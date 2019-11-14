<?php

namespace AwsSdk2\Guzzle\Service\Command\LocationVisitor\Request;

use AwsSdk2\Guzzle\Http\Message\RequestInterface;
use AwsSdk2\Guzzle\Service\Command\CommandInterface;
use AwsSdk2\Guzzle\Service\Description\Parameter;

/**
 * Visitor used to apply a parameter to a request's query string
 */
class QueryVisitor extends AbstractRequestVisitor
{
    public function visit(CommandInterface $command, RequestInterface $request, Parameter $param, $value)
    {
        $request->getQuery()->set($param->getWireName(), $this->prepareValue($value, $param));
    }
}
