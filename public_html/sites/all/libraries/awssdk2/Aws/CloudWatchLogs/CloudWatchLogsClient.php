<?php

namespace AwsSdk2\Aws\CloudWatchLogs;

use AwsSdk2\Aws\Common\Client\AbstractClient;
use AwsSdk2\Aws\Common\Client\ClientBuilder;
use AwsSdk2\Aws\Common\Enum\ClientOptions as Options;
use AwsSdk2\Aws\Common\Exception\Parser\JsonQueryExceptionParser;
use AwsSdk2\Guzzle\Common\Collection;
use AwsSdk2\Guzzle\Service\Resource\Model;

/**
 * Client to interact with Amazon CloudWatch Logs
 *
 * @method Model createLogGroup(array $args = array()) {@command CloudWatchLogs CreateLogGroup}
 * @method Model createLogStream(array $args = array()) {@command CloudWatchLogs CreateLogStream}
 * @method Model deleteLogGroup(array $args = array()) {@command CloudWatchLogs DeleteLogGroup}
 * @method Model deleteLogStream(array $args = array()) {@command CloudWatchLogs DeleteLogStream}
 * @method Model deleteMetricFilter(array $args = array()) {@command CloudWatchLogs DeleteMetricFilter}
 * @method Model deleteRetentionPolicy(array $args = array()) {@command CloudWatchLogs DeleteRetentionPolicy}
 * @method Model describeLogGroups(array $args = array()) {@command CloudWatchLogs DescribeLogGroups}
 * @method Model describeLogStreams(array $args = array()) {@command CloudWatchLogs DescribeLogStreams}
 * @method Model describeMetricFilters(array $args = array()) {@command CloudWatchLogs DescribeMetricFilters}
 * @method Model getLogEvents(array $args = array()) {@command CloudWatchLogs GetLogEvents}
 * @method Model putLogEvents(array $args = array()) {@command CloudWatchLogs PutLogEvents}
 * @method Model putMetricFilter(array $args = array()) {@command CloudWatchLogs PutMetricFilter}
 * @method Model putRetentionPolicy(array $args = array()) {@command CloudWatchLogs PutRetentionPolicy}
 * @method Model testMetricFilter(array $args = array()) {@command CloudWatchLogs TestMetricFilter}
 *
 * @link http://docs.aws.amazon.com/aws-sdk-php/v2/guide/service-cloudwatchlogs.html User guide
 * @link http://docs.aws.amazon.com/aws-sdk-php/v2/api/class-Aws.CloudWatchLogs.CloudWatchLogsClient.html API docs
 */
class CloudWatchLogsClient extends AbstractClient
{
    const LATEST_API_VERSION = '2014-03-28';

    /**
     * Factory method to create a new Amazon CloudWatch Logs client using an array of configuration options.
     *
     * See http://docs.aws.amazon.com/aws-sdk-php/v2/guide/configuration.html#client-configuration-options
     *
     * @param array|Collection $config Client configuration data
     *
     * @return self
     * @link http://docs.aws.amazon.com/aws-sdk-php/v2/guide/configuration.html#client-configuration-options
     */
    public static function factory($config = array())
    {
        return ClientBuilder::factory(__NAMESPACE__)
            ->setConfig($config)
            ->setConfigDefaults(array(
                Options::VERSION             => self::LATEST_API_VERSION,
                Options::SERVICE_DESCRIPTION => __DIR__ . '/Resources/cloudwatchlogs-%s.php'
            ))
            ->setExceptionParser(new JsonQueryExceptionParser())
            ->build();
    }
}
