#include "exportdata.hpp"


ExportData::ExportData(QObject *parent) : QObject(parent)
{
}

ExportData::ExportData(const ExportData &other)
    : QObject(other.parent())
{
    m_useWrapperDirectory = other.m_useWrapperDirectory;
    m_wrapperDirectoryNamePattern = other.m_wrapperDirectoryNamePattern;
    m_directoryPrefix = other.m_directoryPrefix;
    m_resourceFileNamePattern = other.m_resourceFileNamePattern;
    m_resourceName = other.m_resourceName;
    m_options = other.m_options;
}

ExportData& ExportData::operator=(const ExportData &other)
{
    m_useWrapperDirectory = other.m_useWrapperDirectory;
    m_wrapperDirectoryNamePattern = other.m_wrapperDirectoryNamePattern;
    m_directoryPrefix = other.m_directoryPrefix;
    m_resourceFileNamePattern = other.m_resourceFileNamePattern;
    m_resourceName = other.m_resourceName;
    m_options = other.m_options;

    setParent(other.parent());

    return *this;
}

bool ExportData::useWrapperDirectory() const
{
    return m_useWrapperDirectory;
}

QString ExportData::wrapperDirectoryNamePattern() const
{
    return m_wrapperDirectoryNamePattern;
}

QString ExportData::directoryPrefix() const
{
    return m_directoryPrefix;
}

QString ExportData::resourceFileNamePattern() const
{
    return m_resourceFileNamePattern;
}

QString ExportData::resourceName() const
{
    return m_resourceName;
}

QList<bool> ExportData::options() const
{
    return m_options;
}

void ExportData::setUseWrapperDirectory(const bool &useWrapperDirectory)
{
    if (m_useWrapperDirectory != useWrapperDirectory)
    {
        m_useWrapperDirectory = useWrapperDirectory;
        emit useWrapperDirectoryChanged(m_useWrapperDirectory);
    }
}

void ExportData::setWrapperDirectoryNamePattern(const QString &wrapperDirectoryNamePattern)
{
    if (m_wrapperDirectoryNamePattern != wrapperDirectoryNamePattern)
    {
        m_wrapperDirectoryNamePattern = wrapperDirectoryNamePattern;
        emit wrapperDirectoryNamePatternChanged(m_wrapperDirectoryNamePattern);
    }
}

void ExportData::setDirectoryPrefix(const QString &directoryPrefix)
{
    if (m_directoryPrefix != directoryPrefix)
    {
        m_directoryPrefix = directoryPrefix;
        emit directoryPrefixChanged(m_directoryPrefix);
    }
}

void ExportData::setResourceFileNamePattern(const QString &resourceFileNamePattern)
{
    if (m_resourceFileNamePattern != resourceFileNamePattern)
    {
        m_resourceFileNamePattern = resourceFileNamePattern;
        emit resourceFileNamePatternChanged(m_resourceFileNamePattern);
    }
}

void ExportData::setResourceName(const QString &resourceName)
{
    if (m_resourceName != resourceName)
    {
        m_resourceName = resourceName;
        emit resourceNameChanged(m_resourceName);
    }
}

void ExportData::setOptions(const QList<bool> &options)
{
    if (m_options != options)
    {
        m_options = options;
        emit optionsChanged(m_options);
    }
}
