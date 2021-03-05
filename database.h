#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QList>
#include "channel.h"
#include "group.h"
#include "soundtrack.h"
#include "playlist.h"

class Database
{
public:
  Database();
  void dbInit();
  void dbClose();
  QList<Group> getGroups();
  QList<Group> addGroup(const QString &);
  QList<Group> addGroups(const QStringList &);
  QList<Group> removeGroup(const Group);
  QList<Group> clearGroups();
  QList<Soundtrack> getTracks();
  QList<Soundtrack> addTrack(const QString &);
  QList<Soundtrack> addTracks(const QStringList &);
  QList<Soundtrack> removeTrack(Soundtrack);
  QList<Soundtrack> clearTracks();
  bool addChannel(const PlaylistInfo &, const ChannelInfo &);
  QList<Channel> addChannels(const QList<Channel>);
  QList<ChannelInfo> getChannelsList();
  ChannelInfo getChannel(const QString &);
  ChannelInfo getChannel(int);
  bool addPlaylist(const PlaylistInfo &);
  PlaylistInfo getPlaylist(const QString &);
  PlaylistInfo getPlaylist(int);


private:
  QSqlDatabase sdb;
  QSqlQuery *query;

};

#endif // DATABASE_H
