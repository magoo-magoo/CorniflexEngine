#pragma once

#include <functional>
#include <map>
#include <mutex>
#include <typeindex>
#include <vector>

#include "Event.hh"

#include <iostream>

namespace corniflex {

typedef std::function<void(Event *)>	t_fptr;

class EventManager {

private:
  std::map<std::type_index, std::vector<t_fptr > >	_eventHandlers;
  std::vector<std::pair<Event*, t_fptr > >		_events;
  mutable std::mutex	_mutexHandlers;
  mutable std::mutex	_mutexEvents;
  bool		_synchronous = false;

  unsigned long long	_nbProcessedEvent = 0;

public:
  // ----- ----- Getters ----- ----- //
  unsigned long long	getNbProcessedEvent() const;

  // ----- ----- Public Members ----- ----- //
  bool		hasHandler(const Event &event) const;
  void		addHandler(const Event &event, t_fptr handler);
  void		removeHandlers(const Event &event);
  void		sendEvent(Event *event, t_fptr func = nullptr);
  void		processLastEvent();
  void		processFirstEvent();
  void		setSynchronous(bool synchronous);

private:
  // ----- ----- Private Members ----- ----- //
  void		processEvent(Event *event, t_fptr func);
};

}
