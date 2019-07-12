#ifndef UTILS_H
#define UTILS_H

#include <QString>

namespace tnk {
namespace utils
{


#define GETTER(type, name, defaultvalue) \
    public:                          \
    type get_##name() const { return m_##name; } \
    private: \
    type m_##name = defaultvalue;


#define GETTER_SETTER(type, name, defaultvalue) \
    public:                          \
    type get_##name() const { return m_##name; } \
    void set_##name(const type& value) { if( m_##name != value) { m_##name = value; emit  name##Changed(value); }} \
    private: \
    type m_##name = defaultvalue;


#define PROPERTY(type, name, defaultValue) \
    Q_SIGNALS: \
    void name##Changed(); \
    public:                          \
    Q_PROPERTY(type name READ get_##name() WRITE set_##name NOTIFY name##Changed)  \
    type get_##name() const { return m_##name; } \
    void set_##name( type value) { m_##name = value; emit  name##Changed(); } \
    private: \
    type m_##name = defaultValue;



QByteArray  fromFile( const QString& fileName);
bool  toFile( const QString& fileName, const QByteArray& data);


//bool loadStyleSheet(const QString& path);

}
}

#endif // UTILS_H
