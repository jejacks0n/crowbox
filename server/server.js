'use strict';

const express = require('express');
const {Server} = require('ws');

const PORT = process.env.PORT || 3000;

const server = express()
  .get('/log_event', ({query}, res) => {
    if (process.env.API_TOKEN !== query['token']) return;
    res.status(204).send();
    wss.clients.forEach((client) => client.send(query['type'] || -1));
  })
  .use((req, res) => res.sendFile('/index.html', {root: __dirname}))
  .listen(PORT, () => console.log(`Listening on ${PORT}`));

const wss = new Server({server});