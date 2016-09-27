<?php

// Added a mime to document bundle of the file entity.
$document_file_type = file_type_load('document');
$document_file_type->mimetypes[] = 'application/postscript';
file_type_save($document_file_type);
