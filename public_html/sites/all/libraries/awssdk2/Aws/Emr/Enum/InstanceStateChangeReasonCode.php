<?php
/**
 * Copyright 2010-2013 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 * http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

namespace AwsSdk2\Aws\Emr\Enum;

use AwsSdk2\Aws\Common\Enum;

/**
 * Contains enumerable InstanceStateChangeReasonCode values
 */
class InstanceStateChangeReasonCode extends Enum
{
    const INTERNAL_ERROR = 'INTERNAL_ERROR';
    const VALIDATION_ERROR = 'VALIDATION_ERROR';
    const INSTANCE_FAILURE = 'INSTANCE_FAILURE';
    const BOOTSTRAP_FAILURE = 'BOOTSTRAP_FAILURE';
    const CLUSTER_TERMINATED = 'CLUSTER_TERMINATED';
}
