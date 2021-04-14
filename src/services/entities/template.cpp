#include "template.hpp"


Template::Template(QObject *parent)
    : QObject(parent), XTableModel<Template>()
{
    m_guid = 0;
}

Template::Template(const QString &name, QObject *parent)
    : QObject(parent), XTableModel<Template>()
{
    m_guid = 0;
    m_name = name;
}

Template::Template(const QString &name, const QString &description, QObject *parent)
    : QObject(parent), XTableModel<Template>()
{
    m_guid = 0;
    m_name = name;
    m_description = description;
}

Template::Template(const QString &name, const QString &description, const bool &useWrapperDirectory, const QString &wrapperDirectoryNamePattern, const QString &resourceFileNamePattern, QObject *parent)
    : QObject(parent), XTableModel<Template>()
{
    m_guid = 0;
    m_name = name;
    m_description = description;
    m_useWrapperDirectory = useWrapperDirectory;
    m_wrapperDirectoryNamePattern = wrapperDirectoryNamePattern;
    m_resourceFileNamePattern = resourceFileNamePattern;
}

Template::Template(const Template &other)
    : QObject(other.parent()), XTableModel<Template>()
{
    m_guid = other.m_guid;
    m_name = other.m_name;
    m_description = other.m_description;
    m_useWrapperDirectory = other.m_useWrapperDirectory;
    m_wrapperDirectoryNamePattern = other.m_wrapperDirectoryNamePattern;
    m_resourceFileNamePattern = other.m_resourceFileNamePattern;
    m_sizes.append(other.m_sizes);
}

Template& Template::operator=(const Template &other)
{
    m_guid = other.m_guid;
    m_name = other.m_name;
    m_description = other.m_description;
    m_useWrapperDirectory = other.m_useWrapperDirectory;
    m_wrapperDirectoryNamePattern = other.m_wrapperDirectoryNamePattern;
    m_resourceFileNamePattern = other.m_resourceFileNamePattern;
    clearSizes();
    m_sizes.append(other.m_sizes);

    setParent(other.parent());

    return *this;
}

Template::~Template()
{
    clearSizes();
}

quint64 Template::guid() const
{
    return m_guid;
}

QString Template::name() const
{
    return m_name;
}

QString Template::description() const
{
    return m_description;
}

bool Template::useWrapperDirectory() const
{
    return m_useWrapperDirectory;
}

QString Template::wrapperDirectoryNamePattern() const
{
    return m_wrapperDirectoryNamePattern;
}

QString Template::wrapperDirectoryPrefix() const
{
    return m_wrapperDirectoryPrefix;
}

QString Template::resourceFileNamePattern() const
{
    return m_resourceFileNamePattern;
}

QList<Size *> Template::sizes() const
{
    return m_sizes;
}

void Template::setGuid(const quint64 &guid)
{
    if (m_guid != guid)
    {
        m_guid = guid;
        emit guidChanged(m_guid);
    }
}

void Template::setName(const QString &name)
{
    if (m_name != name)
    {
        m_name = name;
        emit nameChanged(m_name);
    }
}

void Template::setDescription(const QString &description)
{
    if (m_description != description)
    {
        m_description = description;
        emit descriptionChanged(m_description);
    }
}

void Template::setUseWrapperDirectory(const bool &useWrapperDirectory)
{
    if (m_useWrapperDirectory != useWrapperDirectory)
    {
        m_useWrapperDirectory = useWrapperDirectory;
        emit useWrapperDirectoryChanged(m_useWrapperDirectory);
    }
}

void Template::setWrapperDirectoryNamePattern(const QString &wrapperDirectoryNamePattern)
{
    if (m_wrapperDirectoryNamePattern != wrapperDirectoryNamePattern)
    {
        m_wrapperDirectoryNamePattern = wrapperDirectoryNamePattern;
        emit wrapperDirectoryNamePatternChanged(m_wrapperDirectoryNamePattern);
    }
}

void Template::setWrapperDirectoryPrefix(const QString &wrapperDirectoryPrefix)
{
    if (m_wrapperDirectoryPrefix != wrapperDirectoryPrefix)
    {
        m_wrapperDirectoryPrefix = wrapperDirectoryPrefix;
        emit wrapperDirectoryPrefixChanged(m_wrapperDirectoryPrefix);
    }
}

void Template::setResourceFileNamePattern(const QString &resourceFileNamePattern)
{
    if (m_resourceFileNamePattern != resourceFileNamePattern)
    {
        m_resourceFileNamePattern = resourceFileNamePattern;
        emit resourceFileNamePatternChanged(m_resourceFileNamePattern);
    }
}

void Template::setSizes(QList<Size *> sizes)
{
    if (m_sizes != sizes)
    {
        clearSizes();
        m_sizes = sizes;
        emit sizesChanged(m_sizes);
    }
}

void Template::clearSizes()
{
    if(!m_sizes.isEmpty())
    {
        foreach (Size* size, m_sizes)
        {
            if(size != nullptr)
            {
                size->deleteLater();
                size = nullptr;
            }
        }
        m_sizes.clear();
    }
}
