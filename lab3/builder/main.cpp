#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <openssl/evp.h>
#include <iomanip>
#include <sstream>

class Article {
public:
    std::wstring title;
    std::wstring authors;
    std::wstring text;
    std::wstring hash;
};

class ArticleBuilder {
public:
    virtual void reset() = 0;

    virtual void buildTitle(const std::wstring &title) = 0;

    virtual void buildAuthors(const std::vector<std::wstring> &authors) = 0;

    virtual void buildText(const std::wstring &text) = 0;

    virtual void buildHash(const std::wstring &hash) = 0;

    virtual Article getResult() = 0;

    virtual ~ArticleBuilder() = default;
};

class ArticleDirector {
private:
    ArticleBuilder *builder;

public:
    explicit ArticleDirector(ArticleBuilder *builder) : builder(builder) {};

    void construct(
            const std::wstring &title,
            const std::vector<std::wstring> &authors,
            const std::wstring &text,
            const std::wstring &hash
    ) {
        builder->buildTitle(title);
        builder->buildAuthors(authors);
        builder->buildText(text);
        builder->buildHash(hash);
    }
};

class XmlArticleBuilder : public ArticleBuilder {
private:
    Article article;

public:
    XmlArticleBuilder() : article() {}

    void reset() override {
        article = Article();
    }

    void buildTitle(const std::wstring &title) override {
        article.title = L"  <title>" + title + L"</title>";
    }

    void buildAuthors(const std::vector<std::wstring> &authors) override {
        article.authors = L"  <authors>\n";
        for (int i = 0; i < authors.size(); i++) {
            article.authors += L"    <author>" + authors[i] + L"</author>\n";
        }
        article.authors += L"  </authors>";
    }

    void buildText(const std::wstring &text) override {
        article.text = L"  <text>" + text + L"  </text>";
    }

    void buildHash(const std::wstring &hash) override {
        article.hash = L"  <hash>" + hash + L"</hash>";
    }

    Article getResult() override {
        return article;
    }
};

std::wstring calculateHash(const std::wstring &text) {
    std::string text_utf8(text.begin(), text.end());

    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (mdctx == nullptr) {
        throw std::runtime_error("Failed to create hash context");
    }

    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), nullptr) != 1) {
        EVP_MD_CTX_free(mdctx);
        throw std::runtime_error("Failed to initialize digest");
    }

    if (EVP_DigestUpdate(mdctx, text_utf8.c_str(), text_utf8.size()) != 1) {
        EVP_MD_CTX_free(mdctx);
        throw std::runtime_error("Failed to update digest");
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int lengthOfHash = 0;
    if (EVP_DigestFinal_ex(mdctx, hash, &lengthOfHash) != 1) {
        EVP_MD_CTX_free(mdctx);
        throw std::runtime_error("Failed to finalize digest");
    }

    EVP_MD_CTX_free(mdctx);

    std::wstringstream wss;
    for (unsigned int i = 0; i < lengthOfHash; ++i) {
        wss << std::setw(2) << std::setfill(L'0') << std::hex << hash[i];
    }

    return wss.str();
}

struct Exception {
    std::wstring message;

    explicit Exception(const std::wstring &message) : message(message) {}
};

void readValues(
        std::wstring &title,
        std::vector<std::wstring> &authors,
        std::wstring &text,
        std::wstring &hash
) {
    std::wifstream input(R"(..\..\..\lab3\builder\article.txt)");

    if (!input.is_open()) {
        throw Exception(L"Невозможно открыть файл article.txt для чтения.");
    }

    getline(input, title);

    std::wstring all, line;
    getline(input, line);
    all += line;
    line += ' ';
    for (int l = 0, r = 0; r < line.size(); r++) {
        if (line[r] == ' ' && l != r) {
            authors.push_back(line.substr(l, r - l));
            l = r + 1;
        }
    }

    while (getline(input, line)) {
        if (input.eof()) {
            hash = line;
            break;
        }
        all += line + L"\n";
        text += line + L"\n";
    }

    input.close();

    std::wstring realHash = calculateHash(all);
    if (hash != realHash) {
        throw Exception(
            L"Указанный хэш '" + hash + L"' статьи не совпадает с фактическим '" + realHash + L"'."
        );
    }
}

void writeValues(Article &article) {
    std::wofstream output(R"(..\..\..\lab3\builder\article.xml)");

    if (!output.is_open()) {
        throw Exception(L"Невозможно открыть файл article.xml для записи.");
    }

    output << "<article>\n" << article.title << '\n' << article.authors << '\n' << article.text << '\n' << article.hash
           << "\n</article>";

    output.close();
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::wstring title;
    std::vector<std::wstring> authors;
    std::wstring text;
    std::wstring hash;

    try {
        readValues(title, authors, text, hash);
    } catch (Exception &e) {
        std::wcout << e.message << std::endl;
        return 0;
    }

    std::unique_ptr<ArticleBuilder> builder = std::make_unique<XmlArticleBuilder>();
    std::unique_ptr<ArticleDirector> director = std::make_unique<ArticleDirector>(builder.get());
    director->construct(title, authors, text, hash);

    Article article = builder->getResult();
    builder->reset();

    try {
        writeValues(article);
    } catch (Exception &e) {
        std::wcout << e.message << std::endl;
    }

    return 0;
}
