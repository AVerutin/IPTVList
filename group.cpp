#include "group.h"

Group::Group()
{
  id = -1;
  name = "";
}

Group::Group(const Group &item)
{
  id = item.id;
  name = item.name;
}

int Group::getId()
{
  return id;
}

void Group::setId(int uid)
{
  id = uid;
}

QString Group::getName()
{
  return name;
}

void Group::setName(const QString &new_name)
{
  name = new_name;
}

