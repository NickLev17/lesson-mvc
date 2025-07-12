#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

/// @brief Абстрактный базовый класс Shape для всех фигур.
///
/// Класс Shape задаёт интерфейс для всех геометрических фигур.
/// Содержит чисто виртуальную функцию draw(), которую должны реализовывать наследники.
class Shape
{
public:
    /// @brief  Конструктор по умолчанию
    Shape() {};

    // Виртуальный деструктор
    virtual ~Shape() = default;

    // Виртуальный метод рисования фигуры
    /// @return Строковое представление фигуры
    virtual string draw() = 0;
};

/// @brief  Класс Squared  наследник класса Shape
class Squared : public Shape
{

public:
    /// @brief  Конструктор по умолчанию
    Squared() { /*cout << "KVADRAAAAAAT\n"; */ }

    ~Squared() {}
    /// Переопределение метода draw()
    string draw() override
    {
        return "SQUARED";
    }
};

/// @brief  Класс Recctangle  наследник класса Shape
class Rectangle : public Shape
{
public:
    /// @brief  Конструктор по умолчанию
    Rectangle() { /*cout << "RECTAAAAANGLE\n"; */ }
    ~Rectangle() {}
    /// Переопределение метода draw()
    string draw() override
    {
        return "RECTANGLE";
    }
};

/// @brief  Класс Circuit  наследник класса Shape
class Circuit : public Shape
{
public:
    /// @brief  Конструктор по умолчанию
    Circuit() {}
    ~Circuit() {}
    /// Переопределение метода draw()
    string draw() override
    {
        return "CIRCUIT";
    }
};

/// @brief  Класс Document
/// Отвечает за работу с документом: создание документа, удаление, чтение.
/// А также отвечает за работу с примитивами документа: добавление, удаление, чтение.
class Document
{

    string name;
    string format;
    string patch;

    /// @brief Набор примитивов
    std::vector<unique_ptr<Shape>> shapes;

public:
    /// Конструктор по умолчанию
    Document() {};

    /// @brief Конструктор с параметрами
    /// @param name_  Имя документа
    /// @param format_  Формат документа
    /// @param patch_  Указание пути документа
    Document(string name_, string format_, string patch_) : name{name_}, format{format_}, patch{patch_} {};
    ~Document() {}
    void setName(const string &name_) { name = name_; };
    void setPatch(const string &patch_) { patch = patch_; };
    void setFormat(const string &format_) { format = format_; };

    string getName() const { return name; };
    string getPatch() const { return patch; };
    string getFormat() const { return format; };

    /// @brief Функция вывода информации о документе.
    /// @return Строкову с указанием всем информации о документе (название, форма, путь).
    string getInformationDocument()
    {

        string temp = getName() + getFormat() + " " + getPatch();

        return temp;
    }

    /// @brief Функция возвращение списка примитивов, содержащихся в документе.
    /// @return Представлен в виде строки
    string getPrimitive()
    {

        string temp;
        if (!shapes.empty()) // СДЕЛАТЬ ОТДЕЛЬНОЙ  ФУНКЦИЕЙ И ВЫВОДИТЬ ВЕСЬ ПИСОК ФИГУР
        {
            for (const auto &s : shapes)
                temp += s.get()->draw() + " ";
        }

        return temp;
    }

    /// @brief  Функция добавления примитива.
    /// @param sh Принятый аргумент перемещаем в вектор примитивов документа.
    void addShape(std::unique_ptr<Shape> sh)
    {

        shapes.push_back(std::move(sh));
    }
    /// @brief Функция удаления примитива.
    /// @param pos Номер тоого примитива, который нужно удалить.
    void removeShape(int pos)
    {

        auto iter = shapes.begin() + pos;
        shapes.erase(iter);
    }

    /// @brief Функция возвращает количество приитивов, содержашихся в документе.
    /// @return Целочисленное значение примитивов.
    int getShapesSize()
    {
        return shapes.size();
    }
};

/// @brief Класс ManageDocument отвечает за работу с документами. Добавление документа, удаление, экспорт , импорт и т.д.
class ManageDocument
{

    /// @brief Текущий номер документа.
    int currentDoc;

public:
    /// @brief Конструктор по умолчанию
    ManageDocument() {};
    ~ManageDocument() {}
    /// @brief  Набор документов
    std::vector<unique_ptr<Document>> docs;

    /// @brief Функция добавление документа в менеджер документов
    /// @param name Имя документа
    /// @param format Формат документа
    /// @param patch Указание пути к документу
    void addDocument(const string &name, const string &format, const string &patch)
    {

        docs.push_back(std::make_unique<Document>(move(name), move(format), move(patch)));
    }

    /// @brief Функция удаления документа, удлаяет последний документ из набора документов.
    void removeDocument()
    {
        if (!docs.empty())
        {
            docs.pop_back();
        }
    }

    /// @brief Функция возвращает информацию о документах из набора докментов.
    /// @return Строовый формат представления
    vector<string> getDocuments()
    {
        vector<string> documents;
        for (int i = 0; i < docs.size(); i++)
        {
            documents.push_back(docs.at(i).get()->getInformationDocument());
        }

        return documents;
    }
    /// @brief Функция экспорта документа в файл.
    /// @param format Документ экспортируется в указаннй формат файла
    void exportDocument(const string &format)
    {
        docs.back().get()->setFormat(format);
    }

    /// @brief Функция импорта документа из файла.
    /// @param sh Передается в качестве аргумента тот файл, который нужно импортировать.
    void importDocument(std::unique_ptr<Document> sh)
    {
        docs.push_back(std::move(sh));
    }
};

/// @brief Класс MyWindow  отвечает за представление данных пользователю
class MyWindow
{
public:
    /// @brief Функция вывода общей информации на экран пользователя.
    /// @param message Сообщение , которое необходимо вывести на экран.
    void showDisplay(const string &message)
    {
        cout << message << "\n";
    };

    /// @brief Функция вывода информационного сообщения о документе на экран пользователя.
    /// @param message Информационного сообщение о документе.
    void showInformationDocument(const string &message)
    {
        cout << "This document - " + message << "\n";
    };

    /// @brief  Функция вывода примитивов на экран пользователя.
    /// @param message Примитивы, которые необходимо вывести на экран.
    void showPrimitive(const string &message)
    {
        cout << "This document has primitives - " + message << "\n";
    };
};

/// @brief Класс Controller  отвечает за общее управление программы.
class Controller
{

public:
    MyWindow &window;
    ManageDocument &manageDoc;

    int current{};

    /// Конструктор с параметрами
    Controller(MyWindow &window_, ManageDocument &manageDoc_) : window{window_}, manageDoc{manageDoc_} {};
    ~Controller() {}
    /// @brief Функция нажатия кнопки "Создать документ"
    /// @param name Имя документа
    /// @param format Формат документа
    /// @param patch Указание пути к документу
    void clickCreateDocument(const string &name, const string &format, const string &patch)
    {
        window.showDisplay("CREATE DOCUMENT: ");
        manageDoc.addDocument(name, format, patch);
        window.showInformationDocument(manageDoc.docs.back().get()->getInformationDocument());
    }

    /// @brief Добавление примитива в текущий документ.
    /// @param sh Умный указатель.
    void addPrimitive(std::unique_ptr<Shape> sh)
    {
        window.showDisplay("CREATE PRIMITIVE: ");
        manageDoc.docs.back().get()->addShape(move(sh));
    }

    /// @brief Функция чтения документа
    /// @param pos Номер того документа, который хотим посмотреть.
    void readDocument(int pos) // is open document and show primitive
    {

        window.showDisplay("READ DOCUMENT: ");

        if (pos < manageDoc.docs.size())
        {
            string primitive = manageDoc.docs.at(pos).get()->getPrimitive();
            if (!primitive.empty())
            {
                window.showDisplay(primitive);
            }
            else
            {

                window.showDisplay("Not prmitive!");
            }
        }
        else
        {
            window.showDisplay("This document NOT FOUND!");
        }
    }

    /// @brief Функция нажатия кнопки "Импорт документа".
    /// @param sh Умный указатель.
    void clickImportDocument(std::unique_ptr<Document> sh)
    {
        window.showDisplay("IMPORT DOCUMENT:");
        manageDoc.importDocument(std::move(sh));
        auto info = manageDoc.docs.back().get()->getInformationDocument();
        window.showInformationDocument(info);
        auto primitive = manageDoc.docs.back().get()->getPrimitive();
        window.showPrimitive(primitive);
    }

    /// @brief Функция нажатия на кнопку "Экспорт документа".
    /// @param format Формат данных.
    void clickExportDocument(const string &format)
    {
        window.showDisplay("EXPORT DOCUMENT: ");
        window.showDisplay(manageDoc.docs.back().get()->getInformationDocument());
        window.showDisplay("EXPORTED IN - ");
        manageDoc.docs.back().get()->setFormat(format);
        window.showDisplay(manageDoc.docs.back().get()->getInformationDocument());
    }
    /// @brief Функция нажатия на кнопку удаления примитива из текущего документа.
    /// @param pos Указание того примитива, который хотим удалить.
    void clickRemovePrimitive(int pos)
    {

        window.showDisplay("REMOVE SHAPE:");
        if (pos < manageDoc.docs.back().get()->getShapesSize())
        {
            manageDoc.docs.back().get()->removeShape(pos);

            window.showDisplay("DELETE SHAPE SUCCES ! Document containce primitive : ");
            window.showDisplay(manageDoc.docs.back().get()->getPrimitive());
        }
        else
        {
            window.showDisplay("THIS DOCUMENT IS NOT SHAPE!");
        }
    }

    /// @brief  Функция нажатия на кнопку "Удаление текущего документа"
    void clickRemoveDocument()
    {

        if (!manageDoc.docs.empty())
        {
            window.showDisplay("REMOVE DOCUMENT: " + manageDoc.docs.back().get()->getInformationDocument());
            manageDoc.docs.pop_back();
            window.showDisplay("All Documents:");
            for (const auto &d : manageDoc.docs)
                window.showDisplay(d.get()->getInformationDocument());
        }
        else
        {
            window.showDisplay("Is not document");
        }
    }
};

int main()
{

    MyWindow window;
    ManageDocument managedoc;
    Controller controller(window, managedoc);

    controller.clickCreateDocument("Paint", ".pnt", "D://game");

    auto docInfo = controller.manageDoc.docs.back().get()->getInformationDocument();
    controller.window.showDisplay(docInfo);
    controller.addPrimitive(std::make_unique<Squared>());
    controller.addPrimitive(std::make_unique<Rectangle>());
    controller.addPrimitive(std::make_unique<Circuit>());

    controller.readDocument(0);

    controller.clickRemovePrimitive(0);

    controller.clickCreateDocument("Text", ".txt", "F://education");
    controller.addPrimitive(std::make_unique<Circuit>());
    controller.addPrimitive(std::make_unique<Squared>());

    controller.readDocument(1);

    controller.clickExportDocument(".html");

    auto doc = std::make_unique<Document>("NewText", ".nwt", "C://lesson");
    doc.get()->addShape(std::make_unique<Squared>());
    controller.clickImportDocument(std::move(doc));

    controller.clickRemoveDocument();

    return 0;
}
