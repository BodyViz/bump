//
//  main.cpp
//  Bump
//
//  Created by Christian Noon on 12/3/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/NotificationCenter.h>

/**
 * The Renderer class is a helper class to help test the NotificationCenter.
 */
class Renderer
{
public:

	/**
	 * Constructor.
	 */
	Renderer(const bump::String& name = "") :
		_name(name),
		_numRenderPasses(2),
		_redrawRequestCount(0)
	{
		// Create a key observer for the requestRedraw() method
		// This looks daunting, but is really quite easy. Just following this example...
		//    - bump::Observer* name = new bump::KeyObserver<this_type>(this, &func_pointer, notification_name);
		bump::Observer* redraw = new bump::KeyObserver<Renderer>(this, &Renderer::requestRedraw, "RequestRedraw");
		ADD_OBSERVER(redraw);

		// Create object observers for the updateNumRenderPasses(), changeName() and changeNameWithString() methods
		// This looks daunting, but is really quite easy. Just following this example...
		//    - bump::Observer* name = new bump::ObjectObserver<this_type, object_type>(this, &func_pointer, notification_name);
		bump::Observer* update = new bump::ObjectObserver<Renderer, unsigned int>(this, &Renderer::updateNumRenderPasses, "UpdateNumRenderPasses");
		bump::Observer* change_name = new bump::ObjectObserver<Renderer, const char*>(this, &Renderer::changeName, "ChangeName");
		bump::Observer* change_name_str = new bump::ObjectObserver<Renderer, bump::String>(this, &Renderer::changeNameWithString, "ChangeNameWithString");
		ADD_OBSERVER(update);
		ADD_OBSERVER(change_name);
		ADD_OBSERVER(change_name_str);
	}

	/**
	 * Destructor.
	 */
	~Renderer()
	{
		std::cout << bump::String("- %1 destructor").arg(_name) << std::endl;
		REMOVE_OBSERVER(this);
	}

	/**
	 * Changes the name of the renderer to the given name.
	 *
	 * @param name the new name to apply to the renderer.
	 */
	void changeName(const char* name)
	{
		std::cout << bump::String("- \"%1\" changed name to \"%2\" using const char* data type.").arg(_name, name) << std::endl;
		_name = name;
	}

	/**
	 * Changes the name of the renderer to the given name.
	 *
	 * @param name the new name to apply to the renderer.
	 */
	void changeNameWithString(const bump::String& name)
	{
		std::cout << bump::String("- \"%1\" changed name to \"%2\" using bump::String data type.").arg(_name, name) << std::endl;
		_name = name;
	}

	/**
	 * Returns the name of the renderer.
	 *
	 * @return the name of the renderer.
	 */
	bump::String name()
	{
		return _name;
	}

	/**
	 * Returns the number of render passes.
	 *
	 * @return the request redraw count.
	 */
	unsigned int numRenderPasses()
	{
		return _numRenderPasses;
	}

	/**
	 * Increments the redraw request count.
	 */
	void requestRedraw()
	{
		std::cout << bump::String("- %1 requesting redraw").arg(_name) << std::endl;
		++_redrawRequestCount;
	}

	/**
	 * Returns the request redraw count.
	 *
	 * @return the request redraw count.
	 */
	unsigned int requestRedrawCount()
	{
		return _redrawRequestCount;
	}

	/**
	 * Updates the number of render passes used.
	 *
	 * @param renderPasses the number of render passes to use.
	 */
	void updateNumRenderPasses(unsigned int numRenderPasses)
	{
		std::cout << bump::String("- %1 update numRenderingPasses: %2").arg(_name, _numRenderPasses) << std::endl;
		_numRenderPasses = numRenderPasses;
	}

protected:

	/** Instance member variables. */
	bump::String _name;
	unsigned int _numRenderPasses;
	unsigned int _redrawRequestCount;
};

/**
 * This example demonstrates how to use the bump NotificationCenter API.
 *
 * The NotificationCenter is a notification system that allows you to send notifications abstractly
 * when events occur in your application. For example, if you're work on an event system, and your event
 * completes, sometimes it would be nice to notify multiple parts of your application that that event
 * was completed. The bump::NotificationCenter makes this type of notification very easy to do. In order
 * to create such a notification, follow these steps:
 *
 * 1) Register all objects as observers with the NotificationCenter
 *       - bump::AbstractObserver* observer = new bump::ObjectObserver<ObjectType, Event*>(this, &ObjectType::eventCompleted, "EventCompleted");
 *       - bump::NotificationCenter::instance()->addObjectObserver(observer);
 *       - ADD_OBSERVER(observer); // convenience macro
 *
 * 2) Make sure to remove the observer from the NotificationCenter in its destructor
 *       - bump::NotificationCenter::instance()->removeObserver(this);
 *       - REMOVE_OBSERVER(this); // convenience macro
 *
 * 3) When the event completes, post a notification that the event completed with a matching name
 *       - bump::NotificationCenter::instance()->postNotificationWithObject("EventCompleted", event);
 *       - POST_NOTIFICATION_WITH_OBJECT("EventCompleted", event); // convenience macro
 *
 * And that's all there is to it! This example shows off some do's and don't's for passing notifications
 * with and without objects. It also demonstrates what will happen if you don't pass objects with the
 * correct type.
 *
 * The most important thing to remember when using the NotificationCenter is to make sure to remove
 * your observers from the NotificationCenter in the observer object's destructor. If you don't do
 * this, you could potentially be sending notifications to NULL which could crash your application.
 * One safe-guard to this is that the NotificationCenter will raise an exception when it is destructed
 * and still contains observers.
 */
int main(int argc, char **argv)
{
	//==============================================================================
	//     Demonstrates how to use notification center inside your own classes
	//==============================================================================

    // Create a few renderers
    Renderer* r1 = new Renderer("Renderer 1");
    Renderer r2("Renderer 2");

	// Post a RequestRedraw notification the long and short way
	std::cout << "Posting \"RequestRedraw\" notifications" << std::endl;
	bump::NotificationCenter::instance()->postNotification("RequestRedraw");
	POST_NOTIFICATION("RequestRedraw");

	// Post an UpdateNumRenderPasses notification the long and short way
	std::cout << "\nPosting \"UpdateNumRenderPasses\" notifications" << std::endl;
	bump::NotificationCenter::instance()->postNotificationWithObject("UpdateNumRenderPasses", (unsigned int) 4);
	POST_NOTIFICATION_WITH_OBJECT("UpdateNumRenderPasses", (unsigned int) 8);

	// If you don't cast the int to an unsigned int, the notification center will throw an exception because the
	// type does not match properly. This is important as it ensures you object passes through the system and comes
	// out the other end properly.
	std::cout << "\nPosting \"UpdateNumRenderPasses\" notification incorrectly" << std::endl;
	try
	{
		POST_NOTIFICATION_WITH_OBJECT("UpdateNumRenderPasses", 8);
	}
	catch (const bump::NotificationError& e)
	{
		std::cout << "- " << e.description() << std::endl;
	}

	// Change the renderer names using the const char* method
	std::cout << "\nPosting \"ChangeName\" notification" << std::endl;
	const char* name1 = "Custom Renderer";
	POST_NOTIFICATION_WITH_OBJECT("ChangeName", name1);

	// Change the renderer names using the bump::String method
	bump::String name2 = "Ultimate Renderer";
	std::cout << "\nPosting \"ChangeNameWithString\" notification" << std::endl;
	POST_NOTIFICATION_WITH_OBJECT("ChangeNameWithString", name2);

	// Cleanup the heap renderer instance
	std::cout << "\nCleaning up the renderers" << std::endl;
	delete r1;

    return 0;
}
