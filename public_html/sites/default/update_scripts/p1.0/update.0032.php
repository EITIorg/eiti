<?php

// Provide a list of modules to be installed.
$modules = array(
  'clone',
);
_us_module__install($modules);

$base64_clone_omitted = "YTo5OntzOjc6ImFydGljbGUiO3M6NzoiYXJ0aWNsZSI7czo4OiJib29rbWFyayI7czo4OiJib29rbWFyayI7czo3OiJtZW50aW9uIjtzOjc6Im1lbnRpb24iO3M6NjoicGVyc29uIjtzOjY6InBlcnNvbiI7czoxNToicHJvZ3Jlc3NfcmVwb3J0IjtzOjE1OiJwcm9ncmVzc19yZXBvcnQiO3M6MTE6InN0YWtlaG9sZGVyIjtzOjExOiJzdGFrZWhvbGRlciI7czo4OiJkb2N1bWVudCI7aTowO3M6ODoiaW50ZXJuYWwiO2k6MDtzOjQ6InBhZ2UiO2k6MDt9";
$serialized_clone_omitted = base64_decode($base64_clone_omitted);
$clone_omitted = unserialize($serialized_clone_omitted);

variable_set('clone_omitted', $clone_omitted);
