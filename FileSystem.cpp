#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

enum FileType
{
    _DIRECTORY,
    _FILE
};

class File
{

public:
    string name;
    int size;
    vector<File *> children;
    FileType type;
    string extension;
    File(string name, int size)
        : name(name), size(size)
    {
        if (name.find('.') != string::npos)
        {
            type = _FILE;
            extension = name.substr(name.find_last_of(".") + 1);
        }
        else
        {
            type = _DIRECTORY;
            extension = "";
        }
    }
};

class Filter
{
public:
    virtual bool isAppliedTo(File *file);
};

class MinSizeFilter : public Filter
{
private:
    int size;

public:
    MinSizeFilter(int size) : size(size) {}

    bool isAppliedTo(File *file)
    {
        return file->size > size;
    };
};

class ExtensionFilter : public Filter
{
private:
    string extension;

public:
    ExtensionFilter(string extension) : extension(extension) {}

    bool isAppliedTo(File *file)
    {
        return file->extension == extension;
    };
};

class FileSystem
{
private:
    vector<Filter *> filters;

public:
    FileSystem() {}
    void addFilter(Filter *filter)
    {
        filters.push_back(filter);
    }

    vector<File *> find(File *root)
    {
        vector<File *> foundFiles;
        if (!root || root->type == _FILE)
        {
            throw invalid_argument("root has to be a directory");
        }
        queue<File *> queue;
        queue.push(root);
        while (!queue.empty())
        {
            File *node = queue.front();
            queue.pop();

            if (node->type == _DIRECTORY)
            {
                for (File *child : node->children)
                {
                    queue.push(child);
                }
            }
            else
            {
                bool isValid = true;
                for (Filter *filter : filters)
                {
                    if (!filter->isAppliedTo(node))
                    {
                        isValid = false;
                        break;
                    }
                }

                if (isValid)
                {
                    foundFiles.push_back(node);
                    cout << "{" << node->name << "}" << endl;
                }
            }
        }

        return foundFiles;
    }
};

int main()
{
    File f1("root_300", 300);

    File f2("fiction_100", 100);
    File f3("action_100", 100);
    File f4("comedy_100", 100);

    // Create child File objects and add them to the children vector
    f1.children.push_back(&f2);
    f1.children.push_back(&f3);
    f1.children.push_back(&f4);

    File f5("StarTrek_4.txt", 4);
    File f6("StarWars_10.xml", 10);
    File f7("JusticeLeague_15.txt", 15);
    File f8("Spock_1.jpg", 1);

    // Create child File objects for f2 and add them to its children vector
    f2.children.push_back(&f5);
    f2.children.push_back(&f6);
    f2.children.push_back(&f7);
    f2.children.push_back(&f8);

    File f9("IronMan_9.txt", 9);
    File f10("MissionImpossible_10.rar", 10);
    File f11("TheLordOfRings_3.zip", 3);

    // Create child File objects for f3 and add them to its children vector
    f3.children.push_back(&f9);
    f3.children.push_back(&f10);
    f3.children.push_back(&f11);

    File f12("BigBangTheory_4.txt", 4);
    File f13("AmericanPie_6.mp3", 6);

    // Create child File objects for f4 and add them to its children vector
    f4.children.push_back(&f12);
    f4.children.push_back(&f13);

    MinSizeFilter greater5Filter(5);
    ExtensionFilter txtFilter("txt");

    FileSystem fileSystem;
    fileSystem.addFilter(&greater5Filter);
    fileSystem.addFilter(&txtFilter);

    vector<File *> res = fileSystem.find(&f1);

    return 0;
}