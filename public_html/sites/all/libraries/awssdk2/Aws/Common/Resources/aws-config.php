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

return array(
    'class' => 'AwsSdk2\\Aws\Common\Aws',
    'services' => array(

        'default_settings' => array(
            'params' => array()
        ),

        'autoscaling' => array(
            'alias'   => 'AutoScaling',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\AutoScaling\AutoScalingClient'
        ),

        'cloudformation' => array(
            'alias'   => 'CloudFormation',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\CloudFormation\CloudFormationClient'
        ),

        'cloudfront' => array(
            'alias'   => 'CloudFront',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\CloudFront\CloudFrontClient'
        ),

        'cloudfront_20120505' => array(
            'extends' => 'cloudfront',
            'params' => array(
                'version' => '2012-05-05'
            )
        ),

        'cloudhsm' => array(
            'alias'   => 'CloudHsm',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\CloudHsm\CloudHsmClient'
        ),

        'cloudsearch' => array(
            'alias'   => 'CloudSearch',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\CloudSearch\CloudSearchClient'
        ),

        'cloudsearch_20110201' => array(
            'extends' => 'cloudsearch',
            'params' => array(
                'version' => '2011-02-01'
            )
        ),

        'cloudsearchdomain' => array(
            'alias'   => 'CloudSearchDomain',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\CloudSearchDomain\CloudSearchDomainClient'
        ),

        'cloudtrail' => array(
            'alias'   => 'CloudTrail',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\CloudTrail\CloudTrailClient'
        ),

        'cloudwatch' => array(
            'alias'   => 'CloudWatch',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\CloudWatch\CloudWatchClient'
        ),

        'cloudwatchlogs' => array(
            'alias'   => 'CloudWatchLogs',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\CloudWatchLogs\CloudWatchLogsClient'
        ),

        'cognito-identity' => array(
            'alias'   => 'CognitoIdentity',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\CognitoIdentity\CognitoIdentityClient'
        ),

        'cognitoidentity' => array('extends' => 'cognito-identity'),

        'cognito-sync' => array(
            'alias'   => 'CognitoSync',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\CognitoSync\CognitoSyncClient'
        ),

        'cognitosync' => array('extends' => 'cognito-sync'),

        'codedeploy' => array(
            'alias'   => 'CodeDeploy',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\CodeDeploy\CodeDeployClient'
        ),

        'config' => array(
            'alias'   => 'ConfigService',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\ConfigService\ConfigServiceClient'
        ),

        'datapipeline' => array(
            'alias'   => 'DataPipeline',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\DataPipeline\DataPipelineClient'
        ),

        'directconnect' => array(
            'alias'   => 'DirectConnect',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\DirectConnect\DirectConnectClient'
        ),

        'dynamodb' => array(
            'alias'   => 'DynamoDb',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\DynamoDb\DynamoDbClient'
        ),

        'dynamodb_20111205' => array(
            'extends' => 'dynamodb',
            'params' => array(
                'version' => '2011-12-05'
            )
        ),

        'ec2' => array(
            'alias'   => 'Ec2',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\Ec2\Ec2Client'
        ),

        'ecs' => array(
            'alias'   => 'Ecs',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\Ecs\EcsClient'
        ),

        'elasticache' => array(
            'alias'   => 'ElastiCache',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\ElastiCache\ElastiCacheClient'
        ),

        'elasticbeanstalk' => array(
            'alias'   => 'ElasticBeanstalk',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\ElasticBeanstalk\ElasticBeanstalkClient'
        ),

        'elasticloadbalancing' => array(
            'alias'   => 'ElasticLoadBalancing',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\ElasticLoadBalancing\ElasticLoadBalancingClient'
        ),

        'elastictranscoder' => array(
            'alias'   => 'ElasticTranscoder',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\ElasticTranscoder\ElasticTranscoderClient'
        ),

        'emr' => array(
            'alias'   => 'Emr',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\Emr\EmrClient'
        ),

        'glacier' => array(
            'alias'   => 'Glacier',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\Glacier\GlacierClient'
        ),

        'kinesis' => array(
            'alias'   => 'Kinesis',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\Kinesis\KinesisClient'
        ),

        'kms' => array(
            'alias'   => 'Kms',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\Kms\KmsClient'
        ),

        'lambda' => array(
            'alias'   => 'Lambda',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\Lambda\LambdaClient'
        ),

        'iam' => array(
            'alias'   => 'Iam',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\Iam\IamClient'
        ),

        'importexport' => array(
            'alias'   => 'ImportExport',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\ImportExport\ImportExportClient'
        ),

        'opsworks' => array(
            'alias'   => 'OpsWorks',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\OpsWorks\OpsWorksClient'
        ),

        'rds' => array(
            'alias'   => 'Rds',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\Rds\RdsClient'
        ),

        'redshift' => array(
            'alias'   => 'Redshift',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\Redshift\RedshiftClient'
        ),

        'route53' => array(
            'alias'   => 'Route53',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\Route53\Route53Client'
        ),

        'route53domains' => array(
            'alias'   => 'Route53Domains',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\Route53Domains\Route53DomainsClient'
        ),

        's3' => array(
            'alias'   => 'S3',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\S3\S3Client'
        ),

        'sdb' => array(
            'alias'   => 'SimpleDb',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\SimpleDb\SimpleDbClient'
        ),

        'ses' => array(
            'alias'   => 'Ses',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\Ses\SesClient'
        ),

        'sns' => array(
            'alias'   => 'Sns',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\Sns\SnsClient'
        ),

        'sqs' => array(
            'alias'   => 'Sqs',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\Sqs\SqsClient'
        ),

        'ssm' => array(
            'alias'   => 'Ssm',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\Ssm\SsmClient'
        ),

        'storagegateway' => array(
            'alias'   => 'StorageGateway',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\StorageGateway\StorageGatewayClient'
        ),

        'sts' => array(
            'alias'   => 'Sts',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\Sts\StsClient'
        ),

        'support' => array(
            'alias'   => 'Support',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\Support\SupportClient'
        ),

        'swf' => array(
            'alias'   => 'Swf',
            'extends' => 'default_settings',
            'class'   => 'AwsSdk2\Aws\Swf\SwfClient'
        ),
    )
);
