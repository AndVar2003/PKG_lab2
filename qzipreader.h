#ifndef QZIPREADER_H
#define QZIPREADER_H

#include <QtCore/qdatetime.h>
#include <QtCore/qfile.h>
#include <QtCore/qstring.h>

QT_BEGIN_NAMESPACE

class QZipReaderPrivate;

class QZipReader
{
public:
    explicit QZipReader(const QString &fileName, QIODevice::OpenMode mode = QIODevice::ReadOnly );

    explicit QZipReader(QIODevice *device);
    ~QZipReader();

    QIODevice* device() const;

    bool isReadable() const;
    bool exists() const;

    struct FileInfo
    {
        FileInfo() noexcept
            : isDir(false), isFile(false), isSymLink(false), crc(0), size(0)
        {}

        bool isValid() const noexcept { return isDir || isFile || isSymLink; }

        QString filePath;
        uint isDir : 1;
        uint isFile : 1;
        uint isSymLink : 1;
        QFile::Permissions permissions;
        uint crc;
        qint64 size;
        QDateTime lastModified;
    };

    QVector<FileInfo> fileInfoList() const;
    int count() const;

    FileInfo entryInfoAt(int index) const;
    QByteArray fileData(const QString &fileName) const;
    bool extractAll(const QString &destinationDir) const;

    enum Status {
        NoError,
        FileReadError,
        FileOpenError,
        FilePermissionsError,
        FileError
    };

    Status status() const;

    void close();

private:
    QZipReaderPrivate *d;
    Q_DISABLE_COPY_MOVE(QZipReader)
};
Q_DECLARE_TYPEINFO(QZipReader::FileInfo, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(QZipReader::Status, Q_PRIMITIVE_TYPE);

QT_END_NAMESPACE

#endif // QZIPREADER_H
