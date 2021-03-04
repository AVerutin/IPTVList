#include "playlist.h"

/// Конструктор по умолчанию
Playlist::Playlist()
{
  listName = "NoName";
  urlTvg = "http://epg.it999.ru/edem.xml.gz";
  autoload = true;
  cache = 500;
  deinterlace = 0;
  tvgShift = 0;
  aspectWidth = 16;
  aspectHeight = 9;
  cropWidth = 0;
  cropHeight = 0;
  cropTop = 0;
  cropLeft = 0;
  refreshPeriod = 0;
  crop = "";
  aspect = "";

  channels = new QList<Channel>;
  channelUid = 0;
  logger = new Logger();
}


/// Перегрузка оператора присваивания
Playlist &Playlist::operator=(const Playlist &source)
{
  // получение параметров свойств списка
  listName = source.listName;
  urlTvg = source.urlTvg;
  autoload = source.autoload;
  cache = source.cache;
  deinterlace = source.deinterlace;
  refreshPeriod = source.refreshPeriod;
  tvgShift = source.tvgShift;
  cropWidth = source.cropWidth;
  cropHeight = source.cropHeight;
  cropTop = source.cropTop;
  cropLeft = source.cropLeft;
  crop = source.crop;
  aspectWidth = source.aspectWidth;
  aspectHeight = source.aspectHeight;
  aspect = source.aspect;
  channels = new QList<Channel>;

  // получение списка каналов
  for(QList<Channel>::iterator it=source.channels->begin(); it!=source.channels->end(); it++)
    {
      channels->append(*it);
    }

  return *this;
}


/// Преобразование в строку
QString Playlist::toString()
{
  QString result;

  // Заголовок листа
  if(!listName.isEmpty())
    {
      result += "#PLAYLIST: " + listName + "\n";
    }

  // Описание листа
  result += "#EXTM3U";

  // Ссылка на программу передач
  if(!urlTvg.isEmpty())
    {
      result += " url-tvg=\"" + urlTvg + "\n";
    }

  // автозагрузка
  if(autoload)
    {
      result += " m3uautoload=\"1\"";
    }

  // кеш
  if(cache>0)
    {
      result += " cache=\"" + QString::number(cache) + "\"";
    }

  // деинтерлейс
  if(deinterlace>0)
    {
      result += " deinterlace=\"" + QString::number(deinterlace) + "\"";
    }

  // соотношение сторон
  if(!aspect.isEmpty())
    {
      result += " aspect-ratio=\"" + aspect + "\"";
    }

  // сдвиг времени
  if(tvgShift>0)
    {
      result += " tvg-shift=\"" + QString::number(tvgShift) + "\"";
    }

  // обрезка кадра
  if(!crop.isEmpty())
    {
      result += " crop=\"" + crop + "\"";
    }

  // период обновления
  if(refreshPeriod>0)
    {
      result += " refresh=\"" + QString::number(refreshPeriod) + "\"";
    }

  // Завершение описания листа
  result += "\n";

  // Добавляем описание каналов
  QList<Channel>::iterator i;
  for(i=channels->begin(); i!=channels->end(); i++)
    {
      result += i->toString();
    }

  return result;
}


/// Установить строковое значение обрезки
void Playlist::setCrop()
{
  if(cropWidth>0 && cropHeight>0)
    {
      crop = QString::number(cropWidth) + "*" + QString::number(cropHeight);
      if(cropTop>0)
        crop += "+" + QString::number(cropTop);
      if(cropLeft>0)
        crop += "+" + QString::number(cropLeft);
    }
}


/// Установить строковое значение соотношения сторон
void Playlist::setAspectRatio()
{
  if(aspectWidth>0 && aspectHeight>0)
    {
      aspect = QString::number(aspectWidth) + "*" + QString::number(aspectHeight);
    }
}


/// Установить обрезку кадра
void Playlist::setCrop(int w, int h, int t, int l)
{
  if(w>0)
    cropWidth = w;
  if(h>0)
    cropHeight = h;
  if(t>0)
    cropTop = t;
  if(l>0)
    cropLeft = l;

  setCrop();
}


/// Установить обрезку по ширине
void Playlist::setCropWidth(int w)
{
  if(w>0)
    cropWidth = w;

  setCrop();
}


/// Установить обрезку по высоте
void Playlist::setCropHeight(int h)
{
  if(h>0)
    cropHeight = h;

  setCrop();
}


/// Установить обрезку сверху
void Playlist::setCropTop(int t)
{
  if(t>0)
    cropTop = t;

  setCrop();
}


/// Установить обрезку слева
void Playlist::setCropLeft(int l)
{
  if(l>0)
    cropLeft = l;

  setCrop();
}


/// Установить обрезку кадра из строки
void Playlist::setCrop(const QString &c)
{
  if(!c.isEmpty())
    crop = c;
}


/// Получить обрезку кадра
QString Playlist::getCrop()
{
  return crop;
}

Cropping Playlist::getCropping()
{
  Cropping res;
  if(!crop.isEmpty())
    {
      // С помощью регулярных выражений
      QStringList cr;
      QRegExp re("([0-9]+)");
      int lastPos = 0;
      while((lastPos = re.indexIn(crop, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString w = re.cap(0);
          cr.append(w);
         }

      switch(cr.size())
        {
        case 0 : break;
        case 1:
          res.width = cr.at(0).toInt();
          break;
        case 2:
          res.width = cr.at(0).toInt();
          res.height = cr.at(1).toInt();
          break;
        case 3:
          res.width = cr.at(0).toInt();
          res.height = cr.at(1).toInt();
          res.top = cr.at(2).toInt();
          break;
        case 4:
          res.width = cr.at(0).toInt();
          res.height = cr.at(1).toInt();
          res.top = cr.at(2).toInt();
          res.left = cr.at(3).toInt();
          break;
        }
    }

  return res;
}


/// Установить соотношение сторон
void Playlist::setAspectRatio(int w, int h)
{
  if(w>0)
    aspectWidth = w;
  if(h>0)
    aspectHeight = h;

  setAspectRatio();
}


/// Установить ширину соотношения сторон
void Playlist::setAspectRatioWidth(int w)
{
  if(w>0)
    aspectWidth = w;

  setAspectRatio();
}


/// Установить высоту соотношения сторон
void Playlist::setAspectRatioHeight(int h)
{
  if(h>0)
    aspectHeight = h;

  setAspectRatio();
}


/// Установить соотношение сторон
void Playlist::setAspectRatio(const QString &ratio)
{
  if(!ratio.isEmpty())
    aspect = ratio;
}


/// Получить соотношение сторон
QString Playlist::getAspectRatio()
{
  return aspect;
}

AspectRatio Playlist::getAspect()
{
  AspectRatio res;
  if(!aspect.isEmpty())
    {
      QString unitName = typeid(this).name();
      logger->info(aspect, unitName);
      // С помощью регулярных выражений
      QStringList cr;
      QRegExp re("([0-9]+)");
      int lastPos = 0;
      while((lastPos = re.indexIn(aspect, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString w = re.cap(0);
          cr.append(w);
         }

      switch(cr.size())
        {
        case 0 : break;
        case 1:
          res.width = cr.at(0).toInt();
          break;
        case 2:
          res.width = cr.at(0).toInt();
          res.height = cr.at(1).toInt();
          break;
        }
    }

  return res;
}


/// Добавить канал в список каналов
int Playlist::addChannel(const Channel &ch)
{
  Channel item = ch;
  channels->append(item);

  return item.getId();
}



/// Получить максимальный номер канала
int Playlist::getMaxId()
{
  int res = -1;
  for(QList<Channel>::iterator it=channels->begin(); it!=channels->end(); it++)
    {
      int id = it->getId();
      if(id>res)
        res = id;
    }

  return res;
}


/// Правка канала
Channel Playlist::editChannel(const Channel &ch)
{
  Channel res = ch;

  return res;
}


/// Удалить канал по номеру позиции в списке
bool Playlist::deleteChannelAt(int)
{
  return false;
}


/// Удалить канал по идентификатору
bool Playlist::deleteChannel(int)
{
  return false;
}


/// Получить количество каналов
int Playlist::getChannelsCount()
{
  return channels->size();
}


/// Получить канал по его номеру
Channel Playlist::getChannelAt(int pos)
{
  Channel res;
  if(pos <= channels->size())
    res = channels->at(pos);

  return res;
}


/// Получить канал по его идентификатору
Channel Playlist::getChannel(int uid)
{
  Channel res;
  for(int i=0; i<channels->size(); i++)
    {
      Channel ch = channels->at(i);
      if(ch.getId() == uid)
        {
          res = ch;
          break;
        }
    }

  return res;
}


/// Наименование списка
void Playlist::setListName(const QString &name)
{
  if(!name.isEmpty())
    listName = name;
}

QString Playlist::getListName()
{
  return listName;
}


/// Ссылка на телегид
void Playlist::setUrlTvg(const QString &epg)
{
  if(!epg.isEmpty())
    urlTvg = epg;
}

QString Playlist::getUrlTvg()
{
  return urlTvg;
}


/// Автозагрузка списка
void Playlist::setAutoload(bool loading)
{
  autoload = loading;
}

bool Playlist::isAutoload()
{
  return autoload;
}


/// Размер кеша
void Playlist::setCache(int c)
{
  if(c>=0)
    cache = c;
}

int Playlist::getCache()
{
  return cache;
}


/// Тип черезстрочности
void Playlist::setDeinterlace(int type)
{
  if(type>=0)
    deinterlace = type;
}

int Playlist::getDeinterlace()
{
  return deinterlace;
}


/// Период обновления
void Playlist::setRefreshPeriod(int ref)
{
  if(ref>=0)
    refreshPeriod = ref;
}

int Playlist::getRefreshPeriod()
{
  return refreshPeriod;
}


/// Сдвиг времени списка
void Playlist::setTvgShift(int shift)
{
  tvgShift = shift;
}

int Playlist::getTvgShift()
{
  return tvgShift;
}


