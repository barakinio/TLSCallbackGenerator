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

  ## Examples

  * Example of CPP syntax
<img align="center" src="https://raw.githubusercontent.com/yoavshah/ImportlessApi/master/images/CPP_Syntax.png" />

  * Example of CPP full example
<img align="center" src="https://raw.githubusercontent.com/yoavshah/ImportlessApi/master/images/CPP_Example.png" />

  * Example's output
<img align="center" src="https://raw.githubusercontent.com/yoavshah/ImportlessApi/master/images/OUTPUT_Example.png" />

  * IDA output (main function)
<img align="center" src="https://raw.githubusercontent.com/yoavshah/ImportlessApi/master/images/IDA_Example_1.png" />

  * IDA output (resolve function)
<img align="center" src="https://raw.githubusercontent.com/yoavshah/ImportlessApi/master/images/IDA_Example_2.png" />


  ## Credits
  * Real thanks for [YoavShah] (https://github.com/JustasMasiulis/lazy_importer/) for creating this project with me 
