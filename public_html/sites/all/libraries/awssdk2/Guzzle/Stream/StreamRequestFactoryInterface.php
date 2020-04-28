<?php

namespace AwsSdk2\Guzzle\Stream;

use AwsSdk2\Guzzle\Http\Message\RequestInterface;

/**
 * Interface used for creating streams from requests
 */
interface StreamRequestFactoryInterface
{
    /**
     * Create a stream based on a request object
     *
     * @param RequestInterface $request Base the stream on a request
     * @param array|resource   $context A stream_context_options resource or array of parameters used to create a
     *                                  stream context.
     * @param array            $params  Optional array of parameters specific to the factory
     *
     * @return StreamInterface Returns a stream object
     * @throws \AwsSdk2\Guzzle\Common\Exception\RuntimeException if the stream cannot be opened or an error occurs
     */
    public function fromRequest(RequestInterface $request, $context = array(), array $params = array());
}
