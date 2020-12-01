CrowBox Server
==============

If you're using the WiFi features of the CrowBox, for instance those capable if you're using a Arduino Uno WiFi Rev 2 instead of an Arduino Uno, you can spin up you own simple node server that can accept events from your CrowBox. These CrowBox events can then be used to alert visitors that something is happening.

This is useful if you want to watch a live feed of your CrowBox. You could also set this up to send push notifications to your phone or similar.

To start, make sure you have node installed (`>=12.17`). You can do this by [downloading the installer](https://nodejs.org/en/download/), or by installing it via a [package manager](https://nodejs.org/en/download/package-manager).

You should then be able to install the dependencies via `npm`.

```shell
$ npm install
```

After all the dependencies are installed, you can start the server.

```shell
$ API_TOKEN=[whatever you set in the CrOS constants] npm start
```

If you browse to [`http://120.0.0.1:3000`](http://120.0.0.1:3000), and trigger events from your CrowBox (depositing a coin, or perch activation) you should be able to see those events come through immediately (or close to immediately) on your browser window.

This could be used to play a sound, or display a notification for instance. We leave this up to you!