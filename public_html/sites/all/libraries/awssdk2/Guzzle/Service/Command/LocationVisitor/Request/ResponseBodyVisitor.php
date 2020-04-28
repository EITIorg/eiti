<?php

namespace AwsSdk2\Guzzle\Service\Command\LocationVisitor\Request;

use AwsSdk2\Guzzle\Http\Message\RequestInterface;
use AwsSdk2\Guzzle\Service\Command\CommandInterface;
use AwsSdk2\Guzzle\Service\Description\Parameter;

/**
 * Visitor used to change the location in which a response body is saved
 */
class ResponseBodyVisitor extends AbstractRequestVisitor
{
    public function visit(CommandInterface $command, RequestInterface $request, Parameter $param, $value)
    {
        $request->setResponseBody($value);
    }
}
