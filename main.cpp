#include <iostream>
#include <filesystem>
#include <algorithm>
#include <vector>

namespace fs = std::filesystem;

struct FileType
{
    std::string name;
    std::vector<std::string> extensions;
};

const std::vector<FileType> FILE_TYPES = {
    {"Images", {".jpg", ".jpeg", ".png", ".gif"}},
    {"Documents", {".txt", ".doc", ".docx", ".pdf"}},
    {"Videos", {".mp4", ".avi", ".mov"}},
    {"Music", {".mp3", ".wav", ".aac"}},
    {"Archives", {".zip", ".tar", ".gz", ".rar"}}};

class FileOrganizer
{
public:
    FileOrganizer(std::string directory_path) : directory_path_m(directory_path) {}

    void organize()
    {
        for (auto &dir_entry : std::filesystem::directory_iterator{directory_path_m})
        {
            if (!dir_entry.is_regular_file())
                continue;
            std::string file_ext = dir_entry.path().extension();
            std::transform(file_ext.begin(), file_ext.end(), file_ext.begin(),
                           [](unsigned char c)
                           { return std::tolower(c); });
            bool type_found = false;

            for (const FileType &type : FILE_TYPES)
            {
                for (const std::string &ext : type.extensions)
                {
                    if (file_ext == ext)
                    {
                        move_file_to_type_directory(dir_entry.path().filename().string(), type);
                        type_found = true;
                    }
                    if (type_found)
                        break;
                }
                if (type_found)
                    break;
            }
        }
    }

private:
    std::string directory_path_m;

    void move_file_to_type_directory(const std::string &file_name, const FileType &type)
    {
        std::string source_file = directory_path_m + "/" + file_name;
        std::string target_dir = directory_path_m + "/" + type.name;
        std::string target_file = target_dir + "/" + file_name;

        std::filesystem::create_directory(target_dir);
        if (fs::exists(fs::path(target_file)))
        {
            target_file = resolve_conflict(target_file);
        }
        std::rename(source_file.c_str(), target_file.c_str());
        std::cout << source_file << " --> " << target_file << std::endl;
    }

    std::string resolve_conflict(std::string file_name)
    {
        int counter = 1;

        fs::path file_path = fs::path(file_name);
        std::string new_name = file_name;

        while (fs::exists(fs::path(new_name)))
        {
            new_name = file_path.parent_path().string() + "/" + file_path.stem().string() +
                       "(" + std::to_string(counter) + ")" + file_path.extension().string();
            counter++;
        }

        return new_name;
    }
};

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: organize <directory_path>" << std::endl;
        return 1;
    }

    std::string directory_path = argv[1];

    if (!fs::exists(directory_path) || !fs::is_directory(directory_path))
    {
        std::cout << "Error: Directory '" << directory_path << "' does not exist." << std::endl;
        return 1;
    }

    FileOrganizer fo{directory_path};
    fo.organize();

    std::cout << "Files organized successfully!" << std::endl;
}
