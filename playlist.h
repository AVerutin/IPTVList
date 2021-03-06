#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QList>

#include "channel.h"
#include "logger.h"

class Playlist
{
public:
  //Методы класса
  Playlist();
  Playlist &operator=(const Playlist &);
  QString toString();
  void setCrop(int w, int h, int t, int l);
  void setCropWidth(int w);
  void setCropHeight(int h);
  void setCropTop(int t);
  void setCropLeft(int l);
  void setCrop(const QString &);
  QString getCrop();
  Cropping getCropping();
  void setAspectRatio(int w, int h);
  void setAspectRatioWidth(int w);
  void setAspectRatioHeight(int h);
  void setAspectRatio(const QString &);
  QString getAspectRatio();
  AspectRatio getAspect();
  int addChannel(const Channel &);
  int getMaxId();
  Channel editChannel(const Channel &);
  bool deleteChannelAt(int);
  bool deleteChannel(int);
  int getChannelsCount();
  Channel getChannelAt(int);
  Channel getChannel(int);
  QList<Channel> getChannelsList();
  void setListName(const QString &);
  QString getListName();
  void setUrlTvg(const QString &);
  QString getUrlTvg();
  void setAutoload(bool);
  bool isAutoload();
  void setCache(int);
  int getCache();
  void setDeinterlace(int);
  int getDeinterlace();
  void setRefreshPeriod(int);
  int getRefreshPeriod();
  void setTvgShift(int);
  int getTvgShift();

private:
  Logger *logger;
  // Свойства класса
  QString listName;
  QString urlTvg;
  bool autoload;
  int cache;
  int deinterlace;
  int refreshPeriod;
  int tvgShift;

  QList<Channel> *channels;
  int channelUid;

  int cropWidth;
  int cropHeight;
  int cropTop;
  int cropLeft;
  QString crop;
  int aspectWidth;
  int aspectHeight;
  QString aspect;

  void setCrop();
  void setAspectRatio();
};

#endif // PLAYLIST_H
