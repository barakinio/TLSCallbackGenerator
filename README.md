# TLSCallbackGenerator
TLSCallbackGenerator is a helper library that allows you to generate TLSCallbacks and nested TLSCallbacks in C++/C.
TLSCallbacks are callback which are defined in the Thread Local Storage data structure. They are executed on the thread startup, before the entry point.
I encourage you to read more on the subject as it can be used in conjunction with various other obfuscation techniques. 

  ## Usage
  ### Option 1 - Regular TLSCallback
  This can be used to create a simple TLSCallback. All you need to do is create a function that you wish to run as a TLSCallback, and call it using the "CREATE_TLS_CALLBACK Macro. 
  For Example:
 `CREATE_TLS_CALLBACK(<tls_callback>);`
  ### Option 2 - Secret TLSCallbacks
  After creating your initial function and registering it as the first item in the Callback array, you can use the "ADD_SECRET_TLS_CALLBACK" Macro to add more callbacks. The advantage is that these callbacks will be added in runtime, so they won't be detected in a static analysis of the PE.
  For example:
   ```
   void tls_callback(PVOID hModule, DWORD dwReason, PVOID pContext)
  {
  ...code...
  
  ADD_SECRET_TLS_CALLBACK(<secret_tls_callback>, <index>);
  ...code...
  }
  ```
  note that you can also add secret TLSCallback from within secret TLSCallbacks! just make sure that the indexes make sense since a Callback will not execute if it's not connected to the rest of the array.
  
  And That's it! your code will run before main. If you're struggling with implementation, check out example.cpp to see how to use both functions.

## Further Functionality
We've also added the option to remove your callbacks from the array. Use the "REMOVE_SECRET_TLS_CALLBACK_BY_INDEX" Macro to do so.

  ## Pics
  These are all taken from an executable which uses both regular and a dynamic TLSCallback, but they apply to both cases.
  
  * PeStudio finds the Static TLSCallback, since it's written in the PE structure of the executable. However, it won't see any dynamic TLSCallback that's present (duh!)
<img align="center" src="https://raw.githubusercontent.com/barakinio/TLSCallbackGenerator/master/images/PeStudio.png" />

  * We can also see the first callback in the exports section, but c'est tout.
<img align="center" src="https://raw.githubusercontent.com/barakinio/TLSCallbackGenerator/master/images/exports.png" />

  * This is how our main will look like. No TLS in sight!
<img align="center" src="https://raw.githubusercontent.com/barakinio/TLSCallbackGenerator/master/images/main.png" />

  * This is how the regular callback looks like. You can see the definition of the dynamic callback (further obfuscation is left as an exercise for the reader). However you won't see any call to it.
<img align="center" src="https://raw.githubusercontent.com/barakinio/TLSCallbackGenerator/master/images/Initial%20callback.png" />



  ## Credits
  * Real thanks for [YoavShah](https://github.com/yoavshah) for creating this project with me 
