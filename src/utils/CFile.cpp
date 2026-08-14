#include "CFile.h"

#include <cerrno>
#include <cstring>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

CFile::CFile(const char *path, const char *mode) { Open(path, mode); }

CFile::CFile(const std::string &path, const char *mode) { Open(path, mode); }

CFile::~CFile() { Close(); }

CFile::CFile(CFile &&other) noexcept
{
    m_file       = other.m_file;
    m_path       = other.m_path;
    other.m_file = nullptr;
    other.m_path.clear();
}

CFile &CFile::operator=(CFile &&other) noexcept
{
    if (this != &other)
    {
        Close();
        m_file       = other.m_file;
        m_path       = other.m_path;
        other.m_file = nullptr;
        other.m_path.clear();
    }

    return *this;
}

bool CFile::Open(const char *path, const char *mode)
{
    Close();
    if (!path || !mode)
    {
        return false;
    }

    m_file = fopen(path, mode);
    if (!m_file)
    {
        m_path.clear();
        return false;
    }

    m_path = path;
    return true;
}

bool CFile::Open(const std::string &path, const char *mode) { return Open(path.c_str(), mode); }

void CFile::Close()
{
    if (m_file)
    {
        fclose(m_file);
        m_file = nullptr;
    }
}

bool CFile::IsOpen() const { return m_file != nullptr; }

FILE *CFile::Handle() const { return m_file; }

const std::string &CFile::Path() const { return m_path; }

size_t CFile::Read(void *buffer, size_t size)
{
    if (!m_file || !buffer || size == 0)
    {
        return 0;
    }

    return fread(buffer, 1, size, m_file);
}

size_t CFile::Write(const void *buffer, size_t size)
{
    if (!m_file || !buffer || size == 0)
    {
        return 0;
    }

    return fwrite(buffer, 1, size, m_file);
}

bool CFile::WriteString(const std::string &text) { return Write(text.data(), text.size()) == text.size(); }

bool CFile::Flush() { return m_file && fflush(m_file) == 0; }

bool CFile::Seek(long offset, SeekOrigin origin) { return m_file && fseek(m_file, offset, ToSeekOrigin(origin)) == 0; }

long CFile::Tell() const { return m_file ? ftell(m_file) : -1; }

long CFile::Size()
{
    if (!m_file)
    {
        return -1;
    }

    long original = Tell();
    if (original < 0 || !Seek(0, SeekOrigin::End))
    {
        return -1;
    }

    long result = Tell();
    Seek(original, SeekOrigin::Begin);
    return result;
}

bool CFile::Eof() const { return m_file && feof(m_file) != 0; }

bool CFile::Exists(const char *path)
{
    if (!path)
    {
        return false;
    }

    struct stat st{};
    return stat(path, &st) == 0;
}

bool CFile::Exists(const std::string &path) { return Exists(path.c_str()); }

bool CFile::IsDirectory(const char *path)
{
    if (!path)
    {
        return false;
    }

    struct stat st{};
    return stat(path, &st) == 0 && S_ISDIR(st.st_mode);
}

bool CFile::IsDirectory(const std::string &path) { return IsDirectory(path.c_str()); }

long CFile::FileSize(const char *path)
{
    if (!path)
    {
        return -1;
    }

    struct stat st{};
    if (stat(path, &st) != 0 || S_ISDIR(st.st_mode))
    {
        return -1;
    }

    return (long) st.st_size;
}

long CFile::FileSize(const std::string &path) { return FileSize(path.c_str()); }

bool CFile::ReadAllBytes(const char *path, std::vector<uint8_t> &out)
{
    out.clear();

    CFile file(path, "rb");
    if (!file.IsOpen())
    {
        return false;
    }

    long length = file.Size();
    if (length < 0)
    {
        return false;
    }

    out.resize((size_t) length);
    return length == 0 || file.Read(out.data(), out.size()) == out.size();
}

bool CFile::ReadAllBytes(const std::string &path, std::vector<uint8_t> &out) { return ReadAllBytes(path.c_str(), out); }

bool CFile::ReadAllText(const char *path, std::string &out)
{
    std::vector<uint8_t> bytes;
    if (!ReadAllBytes(path, bytes))
    {
        out.clear();
        return false;
    }

    out.assign((const char *) bytes.data(), bytes.size());
    return true;
}

bool CFile::ReadAllText(const std::string &path, std::string &out) { return ReadAllText(path.c_str(), out); }

bool CFile::WriteAllBytes(const char *path, const void *data, size_t size)
{
    CFile file(path, "wb");
    if (!file.IsOpen())
    {
        return false;
    }

    if (size != 0 && (!data || file.Write(data, size) != size))
    {
        return false;
    }

    return file.Flush();
}

bool CFile::WriteAllBytes(const std::string &path, const void *data, size_t size) { return WriteAllBytes(path.c_str(), data, size); }

bool CFile::WriteAllText(const char *path, const std::string &text) { return WriteAllBytes(path, text.data(), text.size()); }

bool CFile::WriteAllText(const std::string &path, const std::string &text) { return WriteAllText(path.c_str(), text); }

bool CFile::AppendAllText(const char *path, const std::string &text)
{
    CFile file(path, "ab");
    return file.IsOpen() && file.WriteString(text) && file.Flush();
}

bool CFile::AppendAllText(const std::string &path, const std::string &text) { return AppendAllText(path.c_str(), text); }

bool CFile::Remove(const char *path) { return path && std::remove(path) == 0; }

bool CFile::Remove(const std::string &path) { return remove(path.c_str()); }

bool CFile::Rename(const char *from, const char *to) { return from && to && std::rename(from, to) == 0; }

bool CFile::Rename(const std::string &from, const std::string &to) { return Rename(from.c_str(), to.c_str()); }

bool CFile::CreateDirectory(const char *path)
{
    if (!path || path[0] == '\0')
    {
        return false;
    }

    if (IsDirectory(path))
    {
        return true;
    }

    return mkdir(path, 0777) == 0 || errno == EEXIST;
}

bool CFile::CreateDirectory(const std::string &path) { return CreateDirectory(path.c_str()); }

bool CFile::CreateDirectories(const char *path)
{
    if (!path || path[0] == '\0')
    {
        return false;
    }

    std::string current;
    for (const char *p = path; *p; ++p)
    {
        current.push_back(*p);
        if (*p == '/' && current.size() > 1 && current.back() == '/')
        {
            continue;
        }

        if ((*p == '/' || *(p + 1) == '\0') && current != "/" && current.back() != ':')
        {
            while (!current.empty() && current.back() == '/')
            {
                current.pop_back();
            }

            if (!current.empty() && !CreateDirectory(current))
            {
                return false;
            }

            if (*p == '/')
            {
                current.push_back('/');
            }
        }
    }

    return true;
}

bool CFile::CreateDirectories(const std::string &path) { return CreateDirectories(path.c_str()); }

bool CFile::ListDirectory(const char *path, std::vector<std::string> &out)
{
    out.clear();

    if (!path || path[0] == '\0')
    {
        return false;
    }

    DIR *dir = opendir(path);
    if (!dir)
    {
        return false;
    }

    struct dirent *entry = nullptr;
    while ((entry = readdir(dir)) != nullptr)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        out.push_back(entry->d_name);
    }

    closedir(dir);
    return true;
}

bool CFile::ListDirectory(const std::string &path, std::vector<std::string> &out) { return ListDirectory(path.c_str(), out); }

std::string CFile::ParentPath(const std::string &path)
{
    size_t pos = path.find_last_of("/\\");
    if (pos == std::string::npos)
    {
        return {};
    }

    return path.substr(0, pos);
}

int CFile::ToSeekOrigin(SeekOrigin origin)
{
    switch (origin)
    {
        case SeekOrigin::Begin: {
            return SEEK_SET;
        }

        case SeekOrigin::Current: {
            return SEEK_CUR;
        }

        case SeekOrigin::End: {
            return SEEK_END;
        }
    }

    return SEEK_SET;
}
