#ifndef QMLCACHE_H
#define QMLCACHE_H

#include <QObject>

///
/// \brief The QmlCache class : QML前端需要缓存的数据
///
class QmlCache : public QObject
{
    Q_OBJECT
public:
    explicit QmlCache(QObject *parent = nullptr);

signals:

};

#endif // QMLCACHE_H
