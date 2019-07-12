#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QWidget>

class MenuButton : public QWidget
{
    Q_OBJECT
public:
    typedef enum Type {
        MenuBarButton,
        MinimizeButton,
        MaximizeButton,
        CloseButton

    }Type;


    explicit MenuButton(MenuButton::Type type, QWidget *parent = nullptr);




signals:
    void clicked();




protected:

    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;


    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;


    Type m_type;
    bool m_hover = false;
    QVector<QLine> m_lines;


};

#endif // MENUBUTTON_H
