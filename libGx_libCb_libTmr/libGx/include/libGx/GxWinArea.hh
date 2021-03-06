#ifndef GXOBJECT_INCLUDED
#define GXOBJECT_INCLUDED

//perhaps we could add a AddDeathNotice to GxWinArea which would call annother
//objects function when this object is deleted.  would make passing pointers
//between objects (necessary) safer
#include <string>
#include <libGx/GxInc.hh>


class GxGeomControl;
class GxOwner;

class GxWinArea
{
public:
  virtual ~GxWinArea(void);

  virtual void Resize(UINT tWidth, UINT tHeight);
  void GetSize(UINT &rWidth, UINT &rHeight);
  //these call Resize internally so no need to overload
  void Width(UINT nWidth);
  void Height(UINT nHeight);
  UINT Width(void) const;
  UINT Height(void) const;

  virtual void Move(int newX, int newY);
  void GetPosition(int &rX, int &rY);
  //these call Move internally so no need to overload
  void X(int nX);
  void Y(int nY);
  int X(void);
  int Y(void);

  virtual UINT GetDesiredWidth(void) const;
  virtual UINT GetDesiredHeight(void) const;

  //if no GxGeomControl, will fill the area given, taking into account
  //the response from ($)Border() calls. (see below)
  virtual void Place(int &lX, int &rX, int &tY, int &bY);

  //for objects that are not GxWin's (GxGhost's ) this probably does not make
  //much sense, but it is needed for GxWins
  virtual void Create(void);
  virtual void Display(void);
  //I would almost like to _not_ provide this function because XUnmapWindow is also
  //a one-line function. The _only_ reason this makes sense to implement is because
  //the Ghost abstraction makes Hide() difficult to implement with XUnmapWindow.
  virtual void Hide(void) = 0;
  //called by the owner's distructor
  virtual void OwnerDeleted(void);

  //time is set to the time of the event which caused the application to want
  //focus. CurrentTime is invalid. Do we really want to return anything?
  virtual bool AcceptFocus(Time eventTime);

  virtual UINT LBorder(void) const;
  virtual UINT RBorder(void) const;
  virtual UINT TBorder(void) const;
  virtual UINT BBorder(void) const;

  virtual void SetGeomControl(const GxGeomControl& rNewControl);

  //implementing this might be nice, however so few objects require it
  //and it maximum/minimum sizes could be easly be implemented by overloading
  //Resize(), so currently it does not make much sense to do it here
  //virtual UINT GetMinWidth(void);
  //virtual UINT GetMinHeight(void);

protected:
  GxWinArea(GxOwner *pOwner);

  GxOwner *pWinAreaOwner;

  UINT width;
  UINT height;
  int x;
  int y;

  //private:
protected:
  GxGeomControl *pGControl; //hate everything having this
private:
  GxWinArea(const GxWinArea &); //unimplemented.
};

#endif //GXOBJECT_INCLUDED
