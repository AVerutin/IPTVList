#include "soundtrack.h"

Soundtrack::Soundtrack()
{
  id = -1;
  name = "";
}

Soundtrack::Soundtrack(const Soundtrack &item)
{
  id = item.id;
  name = item.name;
}

int Soundtrack::getId()
{
  return id;
}

void Soundtrack::setId(int uid)
{
  id = uid;
}

QString Soundtrack::getName()
{
  return name;
}

void Soundtrack::setName(const QString &new_name)
{
  name = new_name;
}

