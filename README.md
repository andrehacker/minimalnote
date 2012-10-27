Ultranote
=========

Ultra-simple tag-based keyboard-optimized note application.

Ultranote was developed for the purpose of learning only (C++11, MVC/MVP, Qt, cross platform dev). The plan is to extend it from time to time and to replace my heavily used Evernote at any time (getting slower and slower).

You can **download** a portable version in the [release folder](https://github.com/andrehacker/ultranote/tree/master/releases)

![Screenshot of early version of Ultranote](https://raw.github.com/andrehacker/ultranote/master/misc/screenshot.png)


Features
---------
* Plain Text Note Editor (markdown to be added)
* Ingredients of a note: Title, tags and content
* Global hotkey ALT-SHIFT-F (currently Windows only)
* Full keyboard optimized (in progress)
* Tray Icon
* Full-Text search, based on Tags, Title and content
* I plan to add learning capabilities later (missing in Evernote)


Implementation
--------------
* Based on C++11, Boost, Qt and sqlite
* Using C++11 style whenever possible: No raw pointers, RAII, no arrays (vectors instead), move-semantics (e.g. return unique_ptr)
* Built with VS2010 (for Qt support). Many C++11 features are not yet available;(
* Based on Model View Presenter approach (Passive View). See below (architecture) for more details
* Only the View is implemented in Qt, but it should be easy to replace the view by another UI framework. Other parts don't have dependencies on Qt (except Logging)
* Uses a mall custom sqlite wrapper (could not find a simple c++11-style wrapper without heavy use of raw pointers)

Architecture
--------------
This is based on a very simple implementation of Model View Presenter.
Model has no way to access View and vice versa. All goes through Presenter. The view is defined by an interface (AbstractView.h) and can be replaced easily (e.g. for testing or using another ui framework).
See this [great comparism of MVP/MVC](http://aviadezra.blogspot.de/2007/07/twisting-mvp-triad-say-hello-to-mvpc.html) or the [even better article](http://martinfowler.com/eaaDev/uiArchs.html) from M. Fowler.


Todo
---------
* Static linking deployment
* The global hotkey is not yet platform independent
* Unit Tests need to be added (should have done this first...)
* Want to replace the Qt logging mechanism by something else. Didn't find a great logging library yet.
* There are tons of pending issues...

