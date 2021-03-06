#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QDataStream>
#include <QWidget>
#include <QSize>
#include <QObject>
#include <QList>
#include <QPointer>
#include <QString>
#include <QImage>
#include <QPluginLoader>
#include <QDir>
#include <QPoint>
#include "plugininterface.h"

enum CurrentOp {
    drawing,
    moving
};


class pluginFactory : public QObject
{
    Q_OBJECT
public:
    pluginFactory();
    void loadPlugin(const QDir &pluginsDir);
    void loadPlugin(const QString &pluginPath);

    VisualObject *getPlugin(const QString &label);
    QVector<QPushButton *> getShapeButton(Command *p);

    ~pluginFactory();
private:
    QVector<QPluginLoader *> pluginLoder;
};

class ScribbleArea;

class ChangeShapeCommand : public Command
{
public:
    ChangeShapeCommand(ScribbleArea *p);
    void execute(const QString &shape);

private:
    ScribbleArea *application;
};


class ScribbleArea : public QWidget
{
    Q_OBJECT
public:
    ScribbleArea();
    ~ScribbleArea();

    bool isModified();
    void setModified(bool status);

    void loadFile(const QString &fileName);
    void saveAsFile(const QString &fileName, QByteArray format);
    void saveFile(const QString &fileName);

    void loadPlugin(const QString &filePath);

    void ShapeChange(const QString & shape);

    const QByteArray &getSuffix();
    const QSize getSize();

    QVector<QPushButton *> getShapeButton();

signals:
    void sizeChanged(const QSize &);
    void redoAvailable(bool isAvailable);
    bool undoAvailable(bool isAvailable);

private slots:
    void setMoveShape();

    void redo();
    void undo();

    void resizeCanvas(const QSize &size);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

private:
    void SetDrawEntity(const QPoint &);
    void SetMoveEntity(const QPoint &point);

    void loadImage(const QString &fileName);
    void loadMyFormat(const QString &fileName);

    QImage canvas, backGround;
    QString currentShape;

    pluginFactory factory;

    QList <VisualObject*> AllShape;
    QList <VisualObject*> cacheShape;

    CurrentOp op;

    VisualObject* drawEntity;
    VisualArea* moveEntity;

    bool modified;
    QByteArray fileSuffix;
};

#endif // SCRIBBLEAREA_H
