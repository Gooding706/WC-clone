#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <string>
#include <sstream>
#include <istream>

struct fileInfo
{
    size_t characterCount;
    size_t lineCount;
    size_t wordCount;
};

fileInfo getFileInfo(std::basic_istream<char, std::char_traits<char>> &stream)
{
    fileInfo info = {0, 0, 0};
    std::string line;
    while (std::getline(stream, line))
    {
        std::stringstream ss(line);
        std::string word;

        while (ss >> word)
        {
            info.wordCount++;
        }

        info.lineCount++;
        info.characterCount += line.length();
    }

    return info;
}

std::ifstream openFile(std::string &path)
{
    std::ifstream file;
    file.open(path);

    return file;
}

void printInfo(const std::unordered_set<char> &argumentSet, fileInfo info)
{
    if (argumentSet.find('c') != argumentSet.end())
    {
        std::cout << info.characterCount << ' ';
    }
    if (argumentSet.find('l') != argumentSet.end())
    {
        std::cout << info.lineCount << ' ';
    }
    if (argumentSet.find('w') != argumentSet.end())
    {
        std::cout << info.wordCount << ' ';
    }
    if (argumentSet.find('m') != argumentSet.end())
    {
        std::cout << info.characterCount << ' ';
    }

    if (argumentSet.size() == 0)
    {
        std::cout << info.lineCount << ' ';
        std::cout << info.wordCount << ' ';
        std::cout << info.characterCount << ' ';
    }
}

int main(int argc, char **argv)
{

    // Assemble a vector of paths
    std::unordered_set<char> argumentSet;
    std::vector<std::string> pathList;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-' && argv[i][1] != '\0')
        {
            argumentSet.insert(argv[i][1]);
        }
        else
        {
            pathList.push_back(argv[i]);
        }
    }

    if (pathList.empty())
    {
        fileInfo info = getFileInfo(std::cin);
        printInfo(argumentSet, info);
         std::cout << '\n';
    }
    else
    {

        for (std::string path : pathList)
        {
            std::ifstream file = openFile(path);
            fileInfo info = getFileInfo(file);
            file.close();

            printInfo(argumentSet, info);
            std::cout << path << '\n';
        }
    }

    return 0;
}