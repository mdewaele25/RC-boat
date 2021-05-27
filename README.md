# RC_boat
This was a summer project in which I built and programmed a remote controlled boat from scratch.

There were no specific goals or requirements I had in mind for this boat, more of an experimentation and expression of my knowledge.
The boat itself had a single Arduino Uno onboard for processing, while the remote controller was another Arduino Uno that received signals via an Android app.

The transmitting uno communicated via hc-05 bluetooth module to the Android device.  The two Unos communicated via 433 MHz RF modules.  The onboard Uno had a motor driver connected to two 12V DC motors.  The boat was constructed using a PVC frame with a foam base.  The Android app output had a throttle and angle controller, although much noise was also generated from the third party app.  This required lots of data parsing required to get readable data.  The transmitter sent the corresponding values to the receiver, which utilized the conditionals for speed and angle to correctly power the motors.

The boat could operate in any gentle water up to a range of roughly 40-50 feet.  It could make sharp enough turns to make a circle with radius 3-4 feet.  It's top speed was 2 miles per hour.

Future improvements are to install larger motors to increase the top speed, improve the robustness of the transmitter and receiver to allow for a farther operational range, and overall improve the water-proofing onboard the boat.

Additionally, there was occasional signal loss which resulted in a complete loss of control of the boat.  This was investigated thoroughly, but was never fixed.  This will need to be fixed before taking the boat in larger bodies of water.
