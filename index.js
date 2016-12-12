/**
 * Copyright (c) 2016-present, Viro Media, Inc.
 * All rights reserved. 
 *
 */
'use strict';

const ReactViro = {
  // Components
  get ViroSceneNavigator() { return require('./components/ViroSceneNavigator'); },
  get ViroScene() { return require('./components/ViroScene'); },
  get ViroBox() { return require('./components/ViroBox'); },
  get Materials() { return require('./components/Material/Materials'); },
  get ViroVideo() { return require('./components/ViroVideo'); },
  get Viro360Video() {return require ('./components/Viro360Video'); },
  get ViroNode() { return require('./components/ViroNode'); },
  get ViroCamera() { return require('./components/ViroCamera'); },
  get ViroOrbitCamera() { return require('./components/ViroOrbitCamera'); },
}

module.exports = ReactViro;
