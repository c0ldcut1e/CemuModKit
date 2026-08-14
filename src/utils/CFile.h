#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

class CFile
{
public:
    enum class SeekOrigin
    {
        Begin,
        Current,
        End,
    };

    CFile() = default;
    CFile(const char *path, const char *mode);
    CFile(const std::string &path, const char *mode);
    ~CFile();

    CFile(const CFile &)            = delete;
    CFile &operator=(const CFile &) = delete;

    CFile(CFile &&other) noexcept;
    CFile &operator=(CFile &&other) noexcept;

    bool Open(const char *path, const char *mode);
    bool Open(const std::string &path, const char *mode);
    void Close();

    bool IsOpen() const;
    FILE *Handle() const;
    const std::string &Path() const;

    size_t Read(void *buffer, size_t size);
    size_t Write(const void *buffer, size_t size);
    bool WriteString(const std::string &text);
    bool Flush();

    bool Seek(long offset, SeekOrigin origin = SeekOrigin::Begin);
    long Tell() const;
    long Size();
    bool Eof() const;

    static bool Exists(const char *path);
    static bool Exists(const std::string &path);
    static bool IsDirectory(const char *path);
    static bool IsDirectory(const std::string &path);
    static long FileSize(const char *path);
    static long FileSize(const std::string &path);

    static bool ReadAllBytes(const char *path, std::vector<uint8_t> &out);
    static bool ReadAllBytes(const std::string &path, std::vector<uint8_t> &out);
    static bool ReadAllText(const char *path, std::string &out);
    static bool ReadAllText(const std::string &path, std::string &out);

    static bool WriteAllBytes(const char *path, const void *data, size_t size);
    static bool WriteAllBytes(const std::string &path, const void *data, size_t size);
    static bool WriteAllText(const char *path, const std::string &text);
    static bool WriteAllText(const std::string &path, const std::string &text);
    static bool AppendAllText(const char *path, const std::string &text);
    static bool AppendAllText(const std::string &path, const std::string &text);

    static bool Remove(const char *path);
    static bool Remove(const std::string &path);
    static bool Rename(const char *from, const char *to);
    static bool Rename(const std::string &from, const std::string &to);
    static bool CreateDirectory(const char *path);
    static bool CreateDirectory(const std::string &path);
    static bool CreateDirectories(const char *path);
    static bool CreateDirectories(const std::string &path);
    static bool ListDirectory(const char *path, std::vector<std::string> &out);
    static bool ListDirectory(const std::string &path, std::vector<std::string> &out);
    static std::string ParentPath(const std::string &path);

private:
    static int ToSeekOrigin(SeekOrigin origin);

    FILE *m_file = nullptr;
    std::string m_path;
};
