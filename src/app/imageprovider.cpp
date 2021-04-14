#include <QSvgRenderer>
#include <QImage>
#include <QPainter>
#include <QFile>

#include "imageprovider.hpp"


ImageProvider::ImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Image)
{
}

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize& requestedSize)
{
    Q_UNUSED(size)
    QString resourcePath;
    QSvgRenderer* renderer;
    bool isDefault = false;

    if(id.contains("defaultLight"))
    {
        resourcePath = ":/img/unknow-picture-light.svg";
        isDefault = true;
    }
    else if(id.contains("defaultDark"))
    {
        resourcePath = ":/img/unknow-picture-dark.svg";
        isDefault = true;
    }
    else
    {
        resourcePath = id;
        isDefault = false;
    }

    if(!isDefault)
    {
        resourcePath = id;
        renderer = new QSvgRenderer(resourcePath);
    }
    else
    {
        QFile resourceFile(resourcePath);
        resourceFile.open(QFile::ReadOnly);
        QByteArray data = resourceFile.readAll();
        renderer = new QSvgRenderer(data);
    }

    QSize svgSize = renderer->defaultSize();
    size = &svgSize;

    QImage image(requestedSize.width(), requestedSize.height(), QImage::Format_ARGB32);
    image.fill(0x00000000);

    QPainter painter(&image);
    renderer->render(&painter);

    renderer->deleteLater();
    renderer = nullptr;

    return image;
}
