--- ./ReactAndroid/src/main/jni/react/jni/CatalystInstanceImpl.cpp	2021-10-12 18:36:58.000000000 -0700
+++ /var/folders/vs/8_b205053dddbcv7btj0w0v80000gn/T/update-Ge4Sm3/merge/OfficeRNHost/ReactAndroid/src/main/jni/react/jni/CatalystInstanceImpl.cpp	2021-10-25 12:22:45.000000000 -0700
@@ -95,6 +95,7 @@
 void CatalystInstanceImpl::registerNatives() {
   registerHybrid({
       makeNativeMethod("initHybrid", CatalystInstanceImpl::initHybrid),
+      makeNativeMethod("createModuleRegistry", CatalystInstanceImpl::createModuleRegistry),
       makeNativeMethod(
           "initializeBridge", CatalystInstanceImpl::initializeBridge),
       makeNativeMethod(
@@ -127,26 +128,39 @@
           CatalystInstanceImpl::handleMemoryPressure),
       makeNativeMethod(
           "getRuntimeExecutor", CatalystInstanceImpl::getRuntimeExecutor),
<<<<<<< HEAD
+      makeNativeMethod("getPointerOfInstancePointer", CatalystInstanceImpl::getPointerOfInstancePointer)
   });
 
=======
+      makeNativeMethod("getPointerOfInstancePointer", CatalystInstanceImpl::getPointerOfInstancePointer),
       makeNativeMethod(
           "warnOnLegacyNativeModuleSystemUse",
           CatalystInstanceImpl::warnOnLegacyNativeModuleSystemUse),
@@ -143,6 +145,23 @@
>>>>>>> 90501d6f25... Merge pull request #1000 from rasaha91/android-patches-fix
   JNativeRunnable::registerNatives();
 }
 
+void CatalystInstanceImpl::createModuleRegistry(
+   jni::alias_ref<JavaMessageQueueThread::javaobject> nativeModulesQueue,
+   jni::alias_ref<jni::JCollection<JavaModuleWrapper::javaobject>::javaobject> javaModules,
+   jni::alias_ref<jni::JCollection<ModuleHolder::javaobject>::javaobject> cxxModules) {
+  moduleMessageQueue_ = std::make_shared<JMessageQueueThread>(nativeModulesQueue);
+
+  moduleRegistry_ = std::make_shared<ModuleRegistry>(
+    buildNativeModuleList(
+       std::weak_ptr<Instance>(instance_),
+       javaModules,
+       cxxModules,
+       moduleMessageQueue_
+       ));
+
+  instance_->setModuleRegistry(moduleRegistry_);
+}
+
 void CatalystInstanceImpl::initializeBridge(
     jni::alias_ref<ReactCallback::javaobject> callback,
     // This executor is actually a factory holder.
     JavaScriptExecutorHolder *jseh,
-    jni::alias_ref<JavaMessageQueueThread::javaobject> jsQueue,
-    jni::alias_ref<JavaMessageQueueThread::javaobject> nativeModulesQueue,
-    jni::alias_ref<jni::JCollection<JavaModuleWrapper::javaobject>::javaobject>
-        javaModules,
-    jni::alias_ref<jni::JCollection<ModuleHolder::javaobject>::javaobject>
-        cxxModules) {
+    jni::alias_ref<JavaMessageQueueThread::javaobject> jsQueue) {
   // TODO mhorowitz: how to assert here?
   // Assertions.assertCondition(mBridge == null, "initializeBridge should be
   // called once");
-  moduleMessageQueue_ =
-      std::make_shared<JMessageQueueThread>(nativeModulesQueue);
+  // moduleMessageQueue_ =
+  //     std::make_shared<JMessageQueueThread>(nativeModulesQueue);
 
   // This used to be:
   //
@@ -165,12 +179,13 @@
   // don't need jsModuleDescriptions any more, all the way up and down the
   // stack.
 
-  moduleRegistry_ = std::make_shared<ModuleRegistry>(buildNativeModuleList(
-      std::weak_ptr<Instance>(instance_),
-      javaModules,
-      cxxModules,
-      moduleMessageQueue_));
+  // moduleRegistry_ = std::make_shared<ModuleRegistry>(buildNativeModuleList(
+  //     std::weak_ptr<Instance>(instance_),
+  //     javaModules,
+  //     cxxModules,
+  //     moduleMessageQueue_));
 
+  // TODO:: Office - Assert that moduleRegistry_ is created .. i.e. not null
   instance_->initializeBridge(
       std::make_unique<JInstanceCallback>(callback, moduleMessageQueue_),
       jseh->getExecutorFactory(),
@@ -280,6 +295,10 @@
   instance_->handleMemoryPressure(pressureLevel);
 }
 
+jlong CatalystInstanceImpl::getPointerOfInstancePointer() {
+  return (jlong) (intptr_t) (&instance_);
+}
+
 jni::alias_ref<CallInvokerHolder::javaobject>
 CatalystInstanceImpl::getJSCallInvokerHolder() {
   if (!jsCallInvokerHolder_) {
