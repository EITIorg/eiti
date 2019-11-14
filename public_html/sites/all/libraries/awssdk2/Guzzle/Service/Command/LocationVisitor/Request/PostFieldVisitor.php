<?php

namespace AwsSdk2\Guzzle\Service\Command\LocationVisitor\Request;

use AwsSdk2\Guzzle\Http\Message\RequestInterface;
use AwsSdk2\Guzzle\Service\Command\CommandInterface;
use AwsSdk2\Guzzle\Service\Description\Parameter;

/**
 * Visitor used to apply a parameter to a POST field
 */
class PostFieldVisitor extends AbstractRequestVisitor
{
    public function visit(CommandInterface $command, RequestInterface $request, Parameter $param, $value)
    {
        $request->setPostField($param->getWireName(), $this->prepareValue($value, $param));
    }
}
