import React, { Component } from 'react';
import { NavigationContainer } from '@react-navigation/native'
import { createStackNavigator } from '@react-navigation/stack'
import welcome from './components/welcome'
import main from './components/main'
import sets from './components/sets'
import setting from './components/setting'
import room from './components/room'
//import rating from './components/rating';

const Stack = createStackNavigator();

const App = () => {
  return (
    <NavigationContainer>
      <Stack.Navigator>
      <Stack.Screen 
        name='Welcome'
        component={welcome}
        options={{headerShown:false}}
        /> 
        <Stack.Screen
        name='main'
        component={main}
        options={{headerShown:false}}
        /> 
        <Stack.Screen
        name='sets'
        component={sets}
        options={{headerShown:false}}
        />
        <Stack.Screen
        name='setting'
        component={setting}
        options={{headerShown:false}}
        />
        <Stack.Screen
        name='room'
        component={room}
        options={{headerShown:false}}
        />
        {/* <Stack.Screen
        name='rating'
        component={rating}
        options={{headerShown:false}}
        />  */}

      </Stack.Navigator>
    </NavigationContainer>
  );
};

export default App;