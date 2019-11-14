<?php

namespace AwsSdk2\Guzzle\Service\Command\LocationVisitor\Response;

use AwsSdk2\Guzzle\Http\Message\Response;
use AwsSdk2\Guzzle\Service\Description\Parameter;
use AwsSdk2\Guzzle\Service\Command\CommandInterface;

/**
 * Location visitor used to add the reason phrase of a response to a key in the result
 */
class ReasonPhraseVisitor extends AbstractResponseVisitor
{
    public function visit(
        CommandInterface $command,
        Response $response,
        Parameter $param,
        &$value,
        $context =  null
    ) {
        $value[$param->getName()] = $response->getReasonPhrase();
    }
}
