Ultranote
=========

Ultra-simple tag-based keyboard-optimized Note application.

I am a heavy user of Evernote, which starts getting slower and slower. So the main goal is to keep it as simple as possible to create and search notes.
This was however developed for learning purposes (C++11, MVC/MVP, Qt, cross platform dev). The plan is to extend it from time to time.

Features
---------
* Plain Text Note Editor (markdown to be added)
* Ingedients of a note: Title, Tags and content
* Global hotkey (currently Windows only)
* Full keyboard optimized (in progress)
* Tray Icon
* Full-Text search, based on Tags, Title and content
* I plan to add learning capabilities later (missing in Evernote)


Implementation
--------------
* Based on C++11, Boost, Qt and sqlite
* Built with VS2010 (for Qt support), so some C++11 features are not available yet.
* Based on Model View Presenter approach (Passive View). See below (architecture) for more details
* Only the View is implemented in Qt, but it should be easy to replace the view by another UI framework. Other parts don't have dependencies on Qt (except Logging)
* Uses a mall custom sqlite wrapper (could not find a simple c++11-style wrapper without heavy use of raw pointers)

Architecture
--------------
This is based on a very simple implementation of Model View Presenter.
Model has no way to access view and vice versa. The view is defined by an interface, all goes through Presenter.
See this [great comparism of MVP/MVC](http://aviadezra.blogspot.de/2007/07/twisting-mvp-triad-say-hello-to-mvpc.html) or the [even better article](http://martinfowler.com/eaaDev/uiArchs.html) from M. Fowler.


Todo
---------
* Static linking deployment
* The global hotkey is not yet platform independent
* Unit Tests need to be added (should have done this first...)
* Want to replace the Qt logging mechanism by something else. Didn't find a great logging library yet.
* There are tons of pending issues...

