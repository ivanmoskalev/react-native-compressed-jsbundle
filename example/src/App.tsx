import * as React from 'react';
import { StyleSheet, View, Text } from 'react-native';
import data from './largefile.json'

export default function App() {
  return (
    <View style={styles.container}>
      <Text>Hello from @ivanmoskalev/react-native-compressed-bundle!</Text>
      <Text>Json object contains {data.length} elements.</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
  },
});
