#ifndef SIZE_HPP
#define SIZE_HPP

#include <QObject>

#include "xtablemodel.hpp"


class Template;

class Size : public QObject, public XTableModel<Size>
{
    Q_OBJECT

    Q_PROPERTY(quint64 guid READ guid WRITE setGuid NOTIFY guidChanged)
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(double scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(quint16 width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(quint16 height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(quint64 templateId READ templateId WRITE setTemplateId NOTIFY templateIdChanged)

    X_TABLE_NAME("sizes")
    X_TABLE_FIELDS(X_FIELD(guid, X_PRIMARY_KEY),
                   X_FIELD(label),
                   X_FIELD(scale),
                   X_FIELD(width),
                   X_FIELD(height),
                   X_FIELD(templateId, "template_id", X_FOREIGN_KEY(Template, X_CASCADE, X_CASCADE)))

public:
    explicit Size(QObject *parent = nullptr);
    Size(const quint64 &guid, const QString &label, const double &scale, const quint16 &width, const quint16 &height, const quint64 &templateId, QObject *parent = nullptr);
    Size(const QString &label, const double &scale, const quint16 &width, const quint16 &height, const quint64 &templateId, QObject *parent = nullptr);
    Size(const Size &other);

    Size& operator=(const Size &other);

    ~Size();

    quint64 guid() const;
    QString label() const;
    double scale() const;
    quint16 width() const;
    quint16 height() const;

    quint64 templateId() const;

public slots:
    void setGuid(const quint64 &guid);
    void setLabel(const QString &label);
    void setScale(const double &scale);
    void setWidth(const quint16 &width);
    void setHeight(const quint16 &height);
    void setTemplateId(const quint64 &templateId);

signals:
    void guidChanged(const quint64 &guid);
    void labelChanged(const QString &label);
    void scaleChanged(const double &scale);
    void widthChanged(const quint16 &width);
    void heightChanged(const quint16 &height);
    void templateIdChanged(const quint64 &templateId);

private:
    quint64 m_guid;
    QString m_label;
    double m_scale;
    quint16 m_width;
    quint16 m_height;
    quint64 m_templateId;
};

#include "template.hpp"

#endif // SIZE_HPP
