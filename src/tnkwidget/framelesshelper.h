#ifndef FRAMELESSHELPER_H
#define FRAMELESSHELPER_H

#include <QMainWindow>
class MenuButton;
class QLabel;


class MainWindowFl : public QMainWindow
{
public:
    MainWindowFl( QWidget *parent = nullptr);

    void apply();




    QLayout *customWidgetLayout() const;

protected:
    QWidget *m_titleWidget = nullptr;
    QLayout *m_titleLayout = nullptr;

    QLayout *m_customWidgetLayout = nullptr;

 MenuButton *m_iconButton = nullptr;
    QLabel *m_titleLabel = nullptr;

    MenuButton *m_minimizeButton = nullptr;
    MenuButton *m_maximizeButton = nullptr;
    MenuButton *m_closeButton = nullptr;

};

#endif // FRAMELESSHELPER_H
