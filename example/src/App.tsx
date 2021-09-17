import * as React from 'react'
import {StyleSheet, Text, View} from 'react-native'
import data from './largefile.json'

export default function App() {
  return (
    <View style={styles.container}>
      <Text style={styles.text}>Hello from @ivanmoskalev/react-native-compressed-bundle!</Text>
      <Text style={styles.text}>Json object contains {data.length} elements.</Text>
    </View>
  )
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    padding: 16,
  },
  text: {
    textAlign: 'center'
  }
})
