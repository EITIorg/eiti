<?php

namespace AwsSdk2\Guzzle\Service\Command\LocationVisitor\Response;

use AwsSdk2\Guzzle\Service\Command\CommandInterface;
use AwsSdk2\Guzzle\Http\Message\Response;
use AwsSdk2\Guzzle\Service\Description\Parameter;

/**
 * {@inheritdoc}
 * @codeCoverageIgnore
 */
abstract class AbstractResponseVisitor implements ResponseVisitorInterface
{
    public function before(CommandInterface $command, array &$result) {}

    public function after(CommandInterface $command) {}

    public function visit(
        CommandInterface $command,
        Response $response,
        Parameter $param,
        &$value,
        $context =  null
    ) {}
}
