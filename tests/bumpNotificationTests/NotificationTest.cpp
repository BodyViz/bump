//
//	NotificationTest.cpp
//	Bump
//
//	Created by Christian Noon on 12/3/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/Environment.h>
#include <bump/NotificationCenter.h>
#include <bump/NotificationError.h>
#include <bump/String.h>

// bumpTest headers
#include "../bumpTest/BaseTest.h"

namespace bumpTest {

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
		// Normally we would add the this pointer as an observer to the notification center here...

//		// Create a key observer for the requestRedraw() method
//		bump::Observer* redraw = new bump::KeyObserver<Renderer>(this, &Renderer::requestRedraw, "RequestRedraw");
//		ADD_OBSERVER(redraw);
//
//		// Create object observers for the updateNumRenderPasses(), changeName() and changeNameWithString() methods
//		bump::Observer* update = new bump::ObjectObserver<Renderer, unsigned int>(this, &Renderer::updateNumRenderPasses, "UpdateNumRenderPasses");
//		bump::Observer* change_name = new bump::ObjectObserver<Renderer, const char*>(this, &Renderer::changeName, "ChangeName");
//		bump::Observer* change_name_str = new bump::ObjectObserver<Renderer, bump::String>(this, &Renderer::changeNameWithString, "ChangeNameWithString");
//		ADD_OBSERVER(update);
//		ADD_OBSERVER(change_name);
//		ADD_OBSERVER(change_name_str);
	}

	/**
	 * Destructor.
	 */
	~Renderer()
	{
		// Normally we would the this pointer from the notification center here
//		REMOVE_OBSERVER(this);
	}

	/**
	 * Changes the name of the renderer to the given name.
	 *
	 * @param name the new name to apply to the renderer.
	 */
	void changeName(const char* name)
	{
		_name = name;
	}

	/**
	 * Changes the name of the renderer to the given name.
	 *
	 * @param name the new name to apply to the renderer.
	 */
	void changeNameWithString(const bump::String& name)
	{
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
		_numRenderPasses = numRenderPasses;
	}

protected:

	/** Instance member variables. */
	bump::String _name;
	unsigned int _numRenderPasses;
	unsigned int _redrawRequestCount;
};

/**
 * This is our main notification center testing class. The SetUp and TearDown
 * methods are executed before the test runs and after it completes. This is
 * where we can add any custom set up for each test without having to add this
 * to "every" test individually.
 */
class NotificationTest : public BaseTest
{
protected:

	/** Run immediately before a test starts. Starts the timer. */
	void SetUp()
	{
		// Call the parent setup method
		BaseTest::SetUp();

		// Create some renderers
		_r1 = new Renderer("Renderer 1");
		_r2 = new Renderer("Renderer 2");
		_r3 = Renderer("Renderer 3");
	}

	/** Invoked immediately after a test finishes. Stops the timer. */
	void TearDown()
	{
		// Call the parent tear down method
		BaseTest::TearDown();

		// Cleanup the heap renderers
		bump::NotificationCenter::instance()->removeObserver(_r1);
		bump::NotificationCenter::instance()->removeObserver(_r2);
		bump::NotificationCenter::instance()->removeObserver(&_r3);
		delete _r1;
		delete _r2;
	}

	/** Instance member variables. */
	Renderer*		_r1;
	Renderer*		_r2;
	Renderer		_r3;
};

TEST_F(NotificationTest, testAddObserver1)
{
	// Add the key observer for the requestRedraw method
	bump::Observer* redraw = new bump::KeyObserver<Renderer>(_r1, &Renderer::requestRedraw, "RequestRedraw");
	ADD_OBSERVER(redraw);

	// Test the default value
	EXPECT_EQ(0, _r1->requestRedrawCount());

	// Push a notification and make sure it went through
	unsigned int observers_notified = POST_NOTIFICATION("RequestRedraw");
	EXPECT_EQ(1, observers_notified);
	EXPECT_EQ(1, _r1->requestRedrawCount());

	// Push another notification
	observers_notified = POST_NOTIFICATION("RequestRedraw");
	EXPECT_EQ(1, observers_notified);
	EXPECT_EQ(2, _r1->requestRedrawCount());
}

TEST_F(NotificationTest, testAddObserver2)
{
	// Add the object observer for the updateNumRenderPasses method
	bump::Observer* update = new bump::ObjectObserver<Renderer, unsigned int>(_r1, &Renderer::updateNumRenderPasses, "UpdateNumRenderPasses");
	ADD_OBSERVER(update);

	// Test the default value
	EXPECT_EQ(2, _r1->numRenderPasses());

	// Push a notification and make sure it went through
	unsigned int num_render_passes = 4;
	unsigned int observers_notified = POST_NOTIFICATION_WITH_OBJECT("UpdateNumRenderPasses", num_render_passes);
	EXPECT_EQ(1, observers_notified);
	EXPECT_EQ(4, _r1->numRenderPasses());

	// Push another notification
	num_render_passes = 8;
	observers_notified = POST_NOTIFICATION_WITH_OBJECT("UpdateNumRenderPasses", num_render_passes);
	EXPECT_EQ(1, observers_notified);
	EXPECT_EQ(8, _r1->numRenderPasses());
}

TEST_F(NotificationTest, testAddObserver3)
{
	// Add the object observer for the changeName method
	bump::Observer* change_name = new bump::ObjectObserver<Renderer, const char*>(_r1, &Renderer::changeName, "ChangeName");
	ADD_OBSERVER(change_name);

	// Test the default value
	EXPECT_STREQ("Renderer 1", _r1->name().c_str());

	// Push a notification and make sure it went through
	const char* new_name = "Renderer 2";
	unsigned int observers_notified = POST_NOTIFICATION_WITH_OBJECT("ChangeName", new_name);
	EXPECT_EQ(1, observers_notified);
	EXPECT_STREQ("Renderer 2", _r1->name().c_str());

	// Push another notification
	new_name = "Renderer 3";
	observers_notified = POST_NOTIFICATION_WITH_OBJECT("ChangeName", new_name);
	EXPECT_EQ(1, observers_notified);
	EXPECT_STREQ("Renderer 3", _r1->name().c_str());
}

TEST_F(NotificationTest, testContainsObserver)
{
	// Add some observers
	bump::Observer* update1 = new bump::ObjectObserver<Renderer, unsigned int>(_r1, &Renderer::updateNumRenderPasses, "UpdateNumRenderPasses");
	bump::Observer* update3 = new bump::ObjectObserver<Renderer, unsigned int>(&_r3, &Renderer::updateNumRenderPasses, "UpdateNumRenderPasses");
	ADD_OBSERVER(update1);
	ADD_OBSERVER(update3);

	// Test the containsObserver method
	EXPECT_TRUE(NOTIFICATION_CENTER()->containsObserver(_r1));
	EXPECT_FALSE(NOTIFICATION_CENTER()->containsObserver(_r2));
	EXPECT_TRUE(NOTIFICATION_CENTER()->containsObserver(&_r3));
}

TEST_F(NotificationTest, testPostNotification)
{
	// Register several notifications for "Renderer 1"
	bump::Observer* redraw = new bump::KeyObserver<Renderer>(_r1, &Renderer::requestRedraw, "RequestRedraw");
	bump::Observer* update = new bump::ObjectObserver<Renderer, unsigned int>(_r1, &Renderer::updateNumRenderPasses, "UpdateNumRenderPasses");
	bump::Observer* change_name = new bump::ObjectObserver<Renderer, const char*>(_r1, &Renderer::changeName, "ChangeName");
	bump::Observer* change_name_str = new bump::ObjectObserver<Renderer, bump::String>(_r1, &Renderer::changeNameWithString, "ChangeNameWithString");
	ADD_OBSERVER(redraw);
	ADD_OBSERVER(update);
	ADD_OBSERVER(change_name);
	ADD_OBSERVER(change_name_str);

	// Register a couple notifications for "Renderer 2"
	redraw = new bump::KeyObserver<Renderer>(_r2, &Renderer::requestRedraw, "RequestRedraw");
	update = new bump::ObjectObserver<Renderer, unsigned int>(_r2, &Renderer::updateNumRenderPasses, "UpdateNumRenderPasses");
	change_name = new bump::ObjectObserver<Renderer, const char*>(_r2, &Renderer::changeName, "ChangeName");
	ADD_OBSERVER(redraw);
	ADD_OBSERVER(update);
	ADD_OBSERVER(change_name);

	// Register a couple notifications for "Renderer 3"
	change_name = new bump::ObjectObserver<Renderer, const char*>(&_r3, &Renderer::changeName, "ChangeName");
	change_name_str = new bump::ObjectObserver<Renderer, bump::String>(&_r3, &Renderer::changeNameWithString, "ChangeNameWithString");
	ADD_OBSERVER(change_name);
	ADD_OBSERVER(change_name_str);

	// Test the redraw callback
	EXPECT_EQ(0, _r1->requestRedrawCount());
	unsigned int observers_notified = POST_NOTIFICATION("RequestRedraw");
	EXPECT_EQ(2, observers_notified);
	EXPECT_EQ(1, _r1->requestRedrawCount());

	// Test the update callback (no observers b/c tied to ObjectObserver)
	EXPECT_EQ(2, _r1->numRenderPasses());
	observers_notified = POST_NOTIFICATION("UpdateNumRenderPasses");
	EXPECT_EQ(0, observers_notified);
	EXPECT_EQ(2, _r1->numRenderPasses());

	// Test the change name callback (no observers b/c tied to ObjectObserver)
	EXPECT_STREQ("Renderer 1", _r1->name().c_str());
	observers_notified = POST_NOTIFICATION("ChangeName");
	EXPECT_EQ(0, observers_notified);
	EXPECT_STREQ("Renderer 1", _r1->name().c_str());

	// Test the change name with string callback (no observers b/c tied to ObjectObserver)
	_r1->changeName("Renderer 1");
	EXPECT_STREQ("Renderer 1", _r1->name().c_str());
	observers_notified = POST_NOTIFICATION("ChangeNameWithString");
	EXPECT_EQ(0, observers_notified);
	EXPECT_STREQ("Renderer 1", _r1->name().c_str());
}

TEST_F(NotificationTest, testPostNotificationWithObject)
{
	// Register several notifications for "Renderer 1"
	bump::Observer* redraw = new bump::KeyObserver<Renderer>(_r1, &Renderer::requestRedraw, "RequestRedraw");
	bump::Observer* update = new bump::ObjectObserver<Renderer, unsigned int>(_r1, &Renderer::updateNumRenderPasses, "UpdateNumRenderPasses");
	bump::Observer* change_name = new bump::ObjectObserver<Renderer, const char*>(_r1, &Renderer::changeName, "ChangeName");
	bump::Observer* change_name_str = new bump::ObjectObserver<Renderer, bump::String>(_r1, &Renderer::changeNameWithString, "ChangeNameWithString");
	ADD_OBSERVER(redraw);
	ADD_OBSERVER(update);
	ADD_OBSERVER(change_name);
	ADD_OBSERVER(change_name_str);

	// Register a couple notifications for "Renderer 2"
	redraw = new bump::KeyObserver<Renderer>(_r2, &Renderer::requestRedraw, "RequestRedraw");
	update = new bump::ObjectObserver<Renderer, unsigned int>(_r2, &Renderer::updateNumRenderPasses, "UpdateNumRenderPasses");
	change_name = new bump::ObjectObserver<Renderer, const char*>(_r2, &Renderer::changeName, "ChangeName");
	ADD_OBSERVER(redraw);
	ADD_OBSERVER(update);
	ADD_OBSERVER(change_name);

	// Register a couple notifications for "Renderer 3"
	change_name = new bump::ObjectObserver<Renderer, const char*>(&_r3, &Renderer::changeName, "ChangeName");
	change_name_str = new bump::ObjectObserver<Renderer, bump::String>(&_r3, &Renderer::changeNameWithString, "ChangeNameWithString");
	ADD_OBSERVER(change_name);
	ADD_OBSERVER(change_name_str);

	// Test the redraw callback (no observers b/c tied to KeyObserver)
	EXPECT_EQ(0, _r1->requestRedrawCount());
	unsigned int observers_notified = POST_NOTIFICATION_WITH_OBJECT("RequestRedraw", 10);
	EXPECT_EQ(0, observers_notified);
	EXPECT_EQ(0, _r1->requestRedrawCount());

	// Test the update callback
	unsigned int num_render_passes = 4;
	EXPECT_EQ(2, _r1->numRenderPasses());
	observers_notified = POST_NOTIFICATION_WITH_OBJECT("UpdateNumRenderPasses", num_render_passes);
	EXPECT_EQ(2, observers_notified);
	EXPECT_EQ(4, _r1->numRenderPasses());

	// Test the change name callback
	const char* new_name = "Renderer 2";
	EXPECT_STREQ("Renderer 1", _r1->name().c_str());
	observers_notified = POST_NOTIFICATION_WITH_OBJECT("ChangeName", new_name);
	EXPECT_EQ(3, observers_notified);
	EXPECT_STREQ("Renderer 2", _r1->name().c_str());

	// Test the change name with string callback
	_r1->changeName("Renderer 1");
	EXPECT_STREQ("Renderer 1", _r1->name().c_str());
	bump::String new_name_str = "Renderer 2";
	observers_notified = POST_NOTIFICATION_WITH_OBJECT("ChangeNameWithString", new_name_str);
	EXPECT_EQ(2, observers_notified);
	EXPECT_STREQ("Renderer 2", _r1->name().c_str());

	// Test pushing an incorrect type
	EXPECT_THROW(POST_NOTIFICATION_WITH_OBJECT("ChangeNameWithString", 10), bump::NotificationError);
}

TEST_F(NotificationTest, testRemoveObserver)
{
	// Add some observers
	bump::Observer* update1 = new bump::ObjectObserver<Renderer, unsigned int>(_r1, &Renderer::updateNumRenderPasses, "UpdateNumRenderPasses");
	bump::Observer* update3 = new bump::ObjectObserver<Renderer, unsigned int>(&_r3, &Renderer::updateNumRenderPasses, "UpdateNumRenderPasses");
	ADD_OBSERVER(update1);
	ADD_OBSERVER(update3);

	// Test to make sure the notification center registered the observers
	EXPECT_TRUE(NOTIFICATION_CENTER()->containsObserver(_r1));
	EXPECT_FALSE(NOTIFICATION_CENTER()->containsObserver(_r2));
	EXPECT_TRUE(NOTIFICATION_CENTER()->containsObserver(&_r3));

	// Remove the observers
	REMOVE_OBSERVER(_r1);
	REMOVE_OBSERVER(_r2);
	REMOVE_OBSERVER(&_r3);

	// Test to make sure all the observers were in fact removed
	EXPECT_FALSE(NOTIFICATION_CENTER()->containsObserver(_r1));
	EXPECT_FALSE(NOTIFICATION_CENTER()->containsObserver(_r2));
	EXPECT_FALSE(NOTIFICATION_CENTER()->containsObserver(&_r3));
}

}	// End of bumpTest namespace
