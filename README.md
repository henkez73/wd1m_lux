# wd1m_lux #
Wemos D1 Mini - BH1750 light sensor, wifi, mqtt

Code uploaded to my Wemos D1 Mini using Atom/PlatformIO.

I wanted my Wemos D1 mini to read the light level in lux from the bh1750 sensor, connect to my WiFi and post the reult every minute on MQTT broker.

Simple wiring diagram also available.

I have followed other peoples examples to put together what I wanted my Wemos D1 mini to do.

I use the lux level reported on the MQTT broker to aid/override my NodeRed setup to have lights come on at sunset on a cloudy day ( see example nodered flow).

