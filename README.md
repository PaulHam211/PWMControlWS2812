# PWMControlWS2812

RC (PWM) controlled NeoPixel strip. 

Configure a pot on your RC transmitter, connect PWM signal from receiver to Digital IO pin 1.
Connect Neopixel strip or singular LEDs (WS2812 RGB LED) to Digital IO pin 4
Define pixel_count to amount of LEDs on strip

PWM values are split into 10 ranges, 10 different effects can be shown depending on position of the pot on the transmitter (and sketch size, currently sketch uses 5,062 bytes (84%) on DigiSpark)
