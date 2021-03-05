#ifndef SOUNDTRACK_H
#define SOUNDTRACK_H

#include <QString>

class Soundtrack
{
public:
  Soundtrack();
  Soundtrack(const Soundtrack &);
  int getId();
  void setId(int);
  QString getName();
  void setName(const QString &);

private:
  int id;
  QString name;
};

#endif // SOUNDTRACK_H
