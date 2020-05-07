/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 * @flow strict-local
 */

'use strict';

const React = require('react');
const ReactNative = require('react-native');
import {Platform} from 'react-native'; // TODO(macOS ISS#2323203)

const nativeImageSource = require('../../../../Libraries/Image/nativeImageSource');
const {Image, StyleSheet, Text, View} = ReactNative;

type Props = $ReadOnly<{||}>;
class ImageCapInsetsExample extends React.Component<Props> {
  render(): React.Node {
    let nativeImage; // [TODO(macOS ISS#2323203)
    if (Platform.OS === 'macos') {
      nativeImage = nativeImageSource({
        macos: 'story-background',
        width: 60,
        height: 60,
      });
    } else {
      nativeImage = nativeImageSource({
        ios: 'story-background',
        width: 60,
        height: 60,
      });
    } // ]TODO(macOS ISS#2323203)

    return (
      <View>
        <View style={styles.background}>
          <Text>capInsets: none</Text>
          <Image
            source={nativeImage} // TODO(macOS ISS#2323203)
            style={styles.storyBackground}
            resizeMode="stretch"
            capInsets={{left: 0, right: 0, bottom: 0, top: 0}}
          />
        </View>
        <View style={[styles.background, {paddingTop: 10}]}>
          <Text>capInsets: 15</Text>
          <Image
            source={nativeImage} // TODO(macOS ISS#2323203)
            style={styles.storyBackground}
            resizeMode="stretch"
            capInsets={{left: 15, right: 15, bottom: 15, top: 15}}
          />
        </View>
      </View>
    );
  }
}

const styles = StyleSheet.create({
  background: {
    backgroundColor: '#F6F6F6',
    justifyContent: 'center',
    alignItems: 'center',
  },
  storyBackground: {
    width: 250,
    height: 150,
    borderWidth: 1,
  },
});

module.exports = ImageCapInsetsExample;