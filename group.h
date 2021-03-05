#ifndef GROUP_H
#define GROUP_H

#include <QString>

class Group
{
public:
  Group();
  Group(const Group &);
  int getId();
  void setId(int);
  QString getName();
  void setName(const QString &);

private:
  int id;
  QString name;

};

#endif // GROUP_H
