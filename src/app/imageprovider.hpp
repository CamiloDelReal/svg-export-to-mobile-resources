#ifndef IMAGEPROVIDER_HPP
#define IMAGEPROVIDER_HPP

#include <QObject>
#include <QQuickImageProvider>


class ImageProvider : public QQuickImageProvider
{
    Q_OBJECT
public:
    explicit ImageProvider();

    QImage requestImage(const QString &id, QSize *size, const QSize& requestedSize) override;

};

#endif // IMAGEPROVIDER_HPP
