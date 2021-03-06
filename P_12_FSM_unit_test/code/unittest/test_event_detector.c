#include "CppUTest/TestHarness.h"

#include "stdio.h"
#include "hal_gpio.h"
#include "event_detector.h"
#include "timer.h"

/* A group of tests to test the module event_detector */
TEST_GROUP(event_detector)
{
    /* This function is executed at the START of each test that belongs to
       this test group */
    void setup()
    {
        printf("\n==================================================\n");
    }

    /* This function is executed at the END of each test that belongs to
       this test group */
    void teardown()
    {
        printf("\n==================================================\n \n \n");
    }
};


/* Test name: test_no_timeout_event
   Purpose: Verify that the function ed_get_event() does not return the event
            TIME_OUT if the timer has not expired
   Test sequence:
        - Start the timer with a duartion of 10
        - Call eh_get_event() once --> this decrements the timer by one
        - Check that the event TIME_OUT is not generated (not returned)    */

/// STUDENTS: To be programmed

TEST(event_detector, test_no_timeout_event)
{
	event_t returned_event;
	
	timer_start(10u);
	
	returned_event = ed_get_event();
	
	printf("Returned event: %d, not wanted event: %d\n", returned_event, TIME_OUT);
    CHECK_TEXT(returned_event != TIME_OUT, "Timeout occured!");

    printf("\n");
}

/// END: To be programmed

/* Test name: test_timeout_event
   Purpose: Verify that the function ed_get_event() does return the event 
            TIME_OUT if the timer expires
   Test sequence:
        - Start the timer with a duartion of 1
        - Call eh_get_event() once --> this decrements the timer to zero
        - Check that the event TIME_OUT is generated and returned          */

/// STUDENTS: To be programmed

TEST(event_detector, test_timeout_event)
{
	event_t returned_event;
	
	timer_start(1u);
	
	returned_event = ed_get_event();
	
	printf("Returned event: %d, expected event: %d\n", returned_event, TIME_OUT);
    CHECK_TEXT(returned_event == TIME_OUT, "Timeout has not occured!");

    printf("\n");
}

/// END: To be programmed

/* Test name: test_edge_detection_no_edge
   Purpose:  Verify that no event is detected if input signal is stable at ZERO
   Test sequence:
        - Initialize the input register (IDR) of GPIOB to 0
                --> GPIOB->IDR = 0x00000000;
        - Call eh_get_event()
        - Check that no event is generated                          */

/// STUDENTS: To be programmed

TEST(event_detector, test_edge_detection_no_edge)
{
	event_t returned_event;
	
	GPIOB->IDR = 0x00000000;	// Set input register (IDR) to zero
	
	returned_event = ed_get_event();
	
	printf("Returned event: %d, expected event: %d\n", returned_event, NO_EVENT);
    CHECK_TEXT(returned_event == NO_EVENT, "An Event has occured!");

    printf("\n");
}

/// END: To be programmed

/* Test name: test_edge_detection_rising
   Purpose:  Verify that an event is detected if input has a rising edge
   Test sequence:
        - Initialize the input register (IDR) of GPIOB to 0
        - Call eh_get_event()
        - Set the input register (IDR) such that GPIOB is one for button CAR_W
        - Call eh_get_event()
        - Check that the event EV_CAR_W is generated               */

/// STUDENTS: To be programmed

TEST(event_detector, test_edge_detection_rising)
{
	event_t returned_event;
	
	GPIOB->IDR = 0x00000000;	// Set input register (IDR) to zero
	
	ed_get_event();
	
	GPIOB->IDR = MASK_CAR_W;	// Set button CAR_W
	
	returned_event = ed_get_event();
	
	printf("Returned event: %d, expected event: %d\n", returned_event, EV_CAR_W);
    CHECK_TEXT(returned_event == EV_CAR_W, "Incorrect Event has occured!");

    printf("\n");
}

/// END: To be programmed

/* Test name: test_edge_detection_falling
   Purpose:  Verify that NO event is detected if input has a falling edge
   Test sequence:
        - Set the input register (IDR) such that GPIOB is one for button CAR_W
        - Call eh_get_event()
        - Set the input register (IDR) such that GPIOB is zero for button CAR_W
        - Call eh_get_event()
        - Check that no event is generated                              */

/// STUDENTS: To be programmed

TEST(event_detector, test_edge_detection_falling)
{
	event_t returned_event;
	
	GPIOB->IDR |= MASK_CAR_W;	// Set button CAR_W
	
	ed_get_event();
	
	GPIOB->IDR &= ~MASK_CAR_W;	// Clear button CAR_W
	
	returned_event = ed_get_event();
	
	printf("Returned event: %d, expected event: %d\n", returned_event, NO_EVENT);
    CHECK_TEXT(returned_event == NO_EVENT, "An Event has occured!");

    printf("\n");
}

/// END: To be programmed
