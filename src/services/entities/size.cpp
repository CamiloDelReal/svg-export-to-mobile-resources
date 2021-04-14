#include "size.hpp"


Size::Size(QObject *parent)
    : QObject(parent), XTableModel<Size>()
{
    m_guid = 0;
    m_scale = 1.0f;
    m_width = 0;
    m_height = 0;
}

Size::Size(const quint64 &guid, const QString &label, const double &scale, const quint16 &width, const quint16 &height, const quint64 &templateId, QObject *parent)
    : QObject(parent), XTableModel<Size>()
{
    m_guid = guid;
    m_label = label;
    m_scale = scale;
    m_width = width;
    m_height = height;
    m_templateId = templateId;
}

Size::Size(const QString &label, const double &scale, const quint16 &width, const quint16 &height, const quint64 &templateId, QObject *parent)
    : QObject(parent), XTableModel<Size>()
{
    m_guid = 0;
    m_label = label;
    m_scale = scale;
    m_width = width;
    m_height = height;
    m_templateId = templateId;
}

Size::Size(const Size &other)
    : QObject(other.parent()), XTableModel<Size>()
{
    m_guid = other.m_guid;
    m_label = other.m_label;
    m_scale = other.m_scale;
    m_width = other.m_width;
    m_height = other.m_height;
    m_templateId = other.m_templateId;
}

Size& Size::operator=(const Size &other)
{
    m_guid = other.m_guid;
    m_label = other.m_label;
    m_scale = other.m_scale;
    m_width = other.m_width;
    m_height = other.m_height;
    m_templateId = other.m_templateId;

    setParent(other.parent());

    return *this;
}

Size::~Size()
{
}

quint64 Size::guid() const
{
    return m_guid;
}

QString Size::label() const
{
    return m_label;
}

double Size::scale() const
{
    return m_scale;
}

quint16 Size::width() const
{
    return m_width;
}

quint16 Size::height() const
{
    return m_height;
}

quint64 Size::templateId() const
{
    return m_templateId;
}

void Size::setGuid(const quint64 &guid)
{
    if (m_guid != guid)
    {
        m_guid = guid;
        emit guidChanged(m_guid);
    }
}

void Size::setLabel(const QString &label)
{
    if (m_label != label)
    {
        m_label = label;
        emit labelChanged(m_label);
    }
}

void Size::setScale(const double &scale)
{
    if (!qFuzzyCompare(m_scale, scale))
    {
        m_scale = scale;
        emit scaleChanged(m_scale);
    }
}

void Size::setWidth(const quint16 &width)
{
    if (m_width != width)
    {
        m_width = width;
        emit widthChanged(m_width);
    }
}

void Size::setHeight(const quint16 &height)
{
    if (m_height != height)
    {
        m_height = height;
        emit heightChanged(m_height);
    }
}

void Size::setTemplateId(const quint64 &templateId)
{
    if (m_templateId != templateId)
    {
        m_templateId = templateId;
        emit templateIdChanged(m_templateId);
    }
}
